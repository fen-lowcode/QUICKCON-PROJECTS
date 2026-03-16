
#include "account.hpp"
#include "logs.hpp"
#include <mariadb/conncpp/Exception.hpp>


auto hashPass = [](std::string pass) {
    unsigned char hash[crypto_hash_sha256_BYTES];
    crypto_hash_sha256(hash, (const unsigned char *)pass.c_str(), pass.size());
    std::stringstream ss;

    // Converts each bytes of the sha256 hash into an integer and then into it's hex character set to two bytes
    for (int i = 0; i < crypto_hash_sha256_BYTES; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    // after the loop converrsion above it then stores it as a string object
    return ss.str();
};

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
        if( hashPass(password) != passwordFromDB) {   
            wxMessageBox("Wrong password please try again", "Login failure", wxOK | wxICON_ERROR);
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

    LOGDEBUG(FILE_LOG, "CHECKING ADMIN STATUS");
    auto stmt = std::unique_ptr<sql::PreparedStatement>(
            conn -> prepareStatement("select isAdmin from USERS where userid = ?")
    ); stmt -> setInt(1, accountinfo.userID);

    try {
        auto res = std::unique_ptr<sql::ResultSet>(stmt -> executeQuery());

        if(res -> next()) {

            // message 
            bool result =  res -> getBoolean("isAdmin");

            if (result == true) {
                LOGINFO(FILE_LOG, "Account is Admin");
                return true;
            } else {
                LOGINFO(FILE_LOG, "Account is not Admin");
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
            std::this_thread::sleep_for(std::chrono::seconds(20));
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
bool Account::checkActiveStatus( std::string firstname, std::string lastname) {
    std::string statement = "SELECT LASTSEEN FROM USERS WHERE FIRSTNAME = ? AND LASTNAME = ? AND (LASTSEEN IS NULL OR LASTSEEN < NOW() - INTERVAL 22 SECOND)";
    auto stmt = std::shared_ptr<sql::PreparedStatement>(conn -> prepareStatement(statement));
    stmt -> setString(1, firstname);
    stmt -> setString(2, lastname);

    try {
        auto res = std::shared_ptr<sql::ResultSet>(stmt -> executeQuery());

        if (res -> next()) {
            return false;
        } else {
            std::stringstream logMessage;
            logMessage << "Attempted Multiple loggin session on User: " << accountinfo.userID << "\n";
            LOGWARNING(FILE_LOG, logMessage.str());
        }

    } catch (sql::SQLException& e) {

        std::cout << "SQL error: " << e.what() << std::endl;
    }

    return true;
}

void Account::updateUserConfiguration(int userID, std::string firstname, std::string lastname, bool isAdmin) {

    std::stringstream logmessage;

    std::string statement = "UPDATE USERS SET FIRSTNAME = ?, LASTNAME = ?, ISADMIN = ? WHERE USERID = ?";
    auto stmt = std::shared_ptr<sql::PreparedStatement>(conn -> prepareStatement(statement));
    stmt -> setString(1, firstname);
    stmt -> setString(2, lastname);
    stmt -> setBoolean(3, isAdmin);
    stmt -> setInt(4, userID);

    try {

        int res = stmt -> executeUpdate();
        logmessage << "User: " << accountinfo.userID << " sucessfully updated User:" << userID << " Configuration";
        LOGINFO(FILE_LOG, logmessage.str());

    } catch(sql::SQLException& e) {

        logmessage << "SQL error: " << e.what() << std::endl;
        LOGERROR(FILE_LOG, logmessage.str());

    }
}
