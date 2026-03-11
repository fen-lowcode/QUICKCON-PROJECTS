
#include "account.hpp"
#include "logs.hpp"
#include <sstream>


// check if the credentials matches from the database
bool Account::autheticateLogin( 
    const std::string& firstname,
    const std::string& lastname,
    const std::string& password
) {

    auto stmt = std::unique_ptr<sql::PreparedStatement>(
        conn->prepareStatement(
            "SELECT USERID, PASSWORD FROM USERS WHERE FIRSTNAME = ? AND LASTNAME = ?"
        )
    );

    stmt -> setString(1, firstname);
    stmt -> setString(2, lastname);


    try{

        auto res = std::unique_ptr<sql::ResultSet>(stmt -> executeQuery());
        LOGINFO(this-> FILE_LOG, "Fetching password from the database");

        if (!res->next()) {  wxMessageBox(
            "User not found", "Login failure", wxOK | wxICON_ERROR);
            LOGWARNING(FILE_LOG, "User was not found in the database");
        } 


        // place the password hash from the database and put it in a temporary variable for comparison
        std::string passwordFromDB = std::string(res->getString("PASSWORD")); 

        // check if password don't matches from what is in the database
        LOGINFO(this-> FILE_LOG, "Checking if input password is correct");

        if( password != passwordFromDB) {   
            wxMessageBox("Wrong password please try again", "Login failure", wxOK | wxICON_ERROR);
            LOGWARNING(FILE_LOG, "Login failure input password don't match");
            return false;
        }

        // assign userID from the database
        accountinfo.userID = res->getInt("userID"); 
    
        std::stringstream logMessage; logMessage << "Login success " << "User: " << accountinfo.userID;
        LOGINFO(FILE_LOG, logMessage.str());

    } catch (sql::SQLException& e) {
        LOGERROR(FILE_LOG, "SQL failure from account authentication");
        std::cout << "SQL error: " << e.what() << std::endl;
        return false;
    }
    return true;
}

std::shared_ptr<sql::Connection> Account::getConnection() {
    return this -> conn;
}


bool Account::checkIsAdmin() {

    auto stmt = std::unique_ptr<sql::PreparedStatement>(
            conn -> prepareStatement("select isAdmin from users where userid = ?")
    ); stmt -> setInt(1, accountinfo.userID);

    try {
        auto res = std::unique_ptr<sql::ResultSet>(stmt -> executeQuery());

        if(res -> next()) {

            // message 
            bool result =  res -> getBoolean("isAdmin");

            if (result == true) {
                std::cout << "is account Admin: true\n";
                return true;
            } else {
                std::cout << "is account Admin: false\n";

                return false;
            }
        }

        
    } catch(sql::SQLException& e) {
        std::cout << "SQL error: " << e.what() << std::endl;
    }

    return false;                                                   
}

 // updates "lastseen column" to the most recent time
void Account::updateActiveStatus() {
    sql::SQLString statement {
        "UPDATE USERS "
            "SET lastseen = NOW() "
            "where userID = ?"
    };
    auto stmt = std::shared_ptr<sql::PreparedStatement> (conn -> prepareStatement(statement));
    stmt -> setInt(1, accountinfo.userID);

    while(true) {
        try {
            stmt -> executeUpdate();
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }

        catch(sql::SQLException& e){
            std::cout << "SQL: Error" << e.what() << std::endl;
            break;
        }
    }

    // Kills th program when this thread fails needs to be refactored
    std::cout << "Account::updateActiveStatus(): failed" << std::endl;
    exit(1);
}

// check if a user is active or not
bool Account::checkActiveStatus(std::string firstname, std::string lastname, std::string password) {
    std::string statement = "SELECT LASTSEEN FROM USERS WHERE FIRSTNAME = ? AND LASTNAME = ? AND PASSWORD = ? AND (LASTSEEN IS NULL OR LASTSEEN < NOW() - INTERVAL 35 SECOND)";
    auto stmt = std::shared_ptr<sql::PreparedStatement>(conn -> prepareStatement(statement));
    stmt -> setString(1, firstname);
    stmt -> setString(2, lastname);
    stmt -> setString(3, password);

    try {
        auto res = std::shared_ptr<sql::ResultSet>(stmt -> executeQuery());

        if (res -> next()) {
            return true;
        }

    } catch (sql::SQLException& e) {
        std::cout << "SQL error: " << e.what() << std::endl;
    }

    return false;
}
