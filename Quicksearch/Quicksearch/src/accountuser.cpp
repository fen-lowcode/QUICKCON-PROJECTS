#include "accountuser.hpp"
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>


// check if the credentials matches from the database
bool Account::autheticateLogin( 
    const std::string& firstname,
    const std::string& lastname,
    const std::string& password
) {

    auto stmt = std::unique_ptr<sql::PreparedStatement>(
        conn->prepareStatement(
            "SELECT USERID, PASSWORD FROM users WHERE FIRSTNAME = ? AND LASTNAME = ?"
        )
    );

    stmt -> setString(1, firstname);
    stmt -> setString(2, lastname);


    try{

        auto res = std::unique_ptr<sql::ResultSet>(stmt -> executeQuery());
        if (!res->next()) {  wxMessageBox("User not found", "Login failure", wxOK | wxICON_ERROR);} 

        // get's th password from the database
        std::string passwordFromDB = std::string(res->getString("PASSWORD")); 

        // check if password don't matches from what is in the database
        if( password != passwordFromDB) {   
            wxMessageBox("Wrong password please try again", "Login failure", wxOK | wxICON_ERROR);
            return false;
        }

        accountinfo.userID = res->getInt("userID"); 
        std::cout << "Welcome! User " << accountinfo.userID << std::endl;

    } catch (sql::SQLException& e) {
        std::cout << "SQL error: " << e.what() << std::endl;
        return false;
    }
    return true;
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
  // ------ TEMPORARY ------

// It prints the name of all the collectors associated with the logged in user
void Account::identifyCollectors() {

    sql::SQLString statement {
        "SELECT u.firstname AS user_firstname, "
        "c.collectorID, "
        "c.firstname AS collector_firstname "
        "FROM users u "
        "INNER JOIN users_to_collectors utc ON u.userID = utc.userID "
        "INNER JOIN collectors c ON c.collectorID = utc.collectorID "
        "WHERE u.userID = ?"
    };
    
    auto stmt = std::unique_ptr<sql::PreparedStatement>(conn -> prepareStatement(statement));
    stmt -> setInt(1, accountinfo.userID);

    // Debug 
    std::cout << "hello: " << accountinfo.userID << std::endl;

    try {
        auto res = std::unique_ptr<sql::ResultSet>(stmt -> executeQuery());

        while(res->next()) {
            std::string collectorName = std::string(res->getString("collector_firstname"));
            std::cout << collectorName << std::endl;
        }

    }  catch(sql::SQLException& e) {
        std::cout << "SQL error: " << e.what();
    }
}

 // updates "lastseen column" to the most recent time
void Account::updateActiveStatus() {
    sql::SQLString statement {
        "UPDATE users "
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
    std::string statement = "SELECT lastseen FROM users WHERE firstname = ? AND lastname = ? AND password = ? AND (lastseen IS NULL OR lastseen < NOW() - INTERVAL 35 SECOND)";
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

User::User(std::shared_ptr<sql::Connection> conn) : Account(conn) {
    this -> conn = conn;
}

void User::setUsername(std::string firstname, std::string lastname) {
    this -> firstname = firstname;
    this -> lastname = lastname;
}


void User::setPassword(std::string password) {
    this -> password = password;
}

std::string User::getFirstName() {
    return this -> firstname;
}


std::string User::getLastName() {
    return this -> lastname;
}

std::string User::getPassword() {
    return this -> password;
}


bool User::login() {
    return autheticateLogin(
        this -> firstname, 
        this -> lastname, 
        this -> password
    );
}

std::string User::fetchUsername() {
    auto convertToUpper = [](std::string username) -> std::string {
        for(char& c: username) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        return username;
    };

    std::string username = convertToUpper(this -> getFirstName() + " " + getLastName());
    return username;
}
