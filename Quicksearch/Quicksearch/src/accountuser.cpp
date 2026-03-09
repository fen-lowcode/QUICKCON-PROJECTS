#include "accountuser.hpp"
#include <mariadb/conncpp/Connection.hpp>
#include <memory>
#include <string>
#include <wx/wx.h>

// refactor this SHIT!!
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

            // debug
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

    sql::SQLString statement = 
        "SELECT u.firstname AS user_firstname, "
        "c.collectorID, "
        "c.firstname AS collector_firstname "
        "FROM users u "
        "INNER JOIN users_to_collectors utc ON u.userID = utc.userID "
        "INNER JOIN collectors c ON c.collectorID = utc.collectorID "
        "WHERE u.userID = ?";
    
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

    std::string username = convertToUpper(firstname + " " + lastname);
    return username;
}
