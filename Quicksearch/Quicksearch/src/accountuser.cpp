#include "accountuser.hpp"
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Exception.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <mariadb/conncpp/SQLString.hpp>
#include <mariadb/conncpp/Statement.hpp>
#include <memory>
#include <string>

// refactor this SHIT!!
bool Account::autheticateLogin(
    std::shared_ptr<sql::Connection> conn, 
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
        if (!res->next()) {  std::cout << "No result\n"; return false;} 

        // get's th password from the database
        std::string passwordFromDB = std::string(res->getString("PASSWORD")); 

        // check if password don't matches from what is in the database
        if( password != passwordFromDB) { std::cout << "Password dont match\n"; return false; }

        accountinfo.userID = res->getInt("userID"); 
        std::cout << "Welcome! User " << accountinfo.userID << std::endl;

    } catch (sql::SQLException& e) {
        std::cout << "SQL error: " << e.what() << std::endl; return false;
    }
    return true;
}

bool Account::checkIsAdmin(std::shared_ptr<sql::Connection> conn) {

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


// bool Account::updateAccessState(std::unique_ptr<sql::Connection> conn) {

//     auto stmt = std::unique_ptr<sql::PreparedStatement>(conn -> prepareStatement(""));
//     try {



//     }  catch(sql::SQLException& e) {
//         std::cout << "SQL error: " << e.what();
//     }
    
//     return true;
// }



void User::useProgram(std::string& firstname, std::string& lastname, std::string& password) {

      // Connect to database
    std::shared_ptr<sql::Connection> conn = connToDB();
    // initialize a log in
    if (autheticateLogin( conn, firstname, lastname, password)) {
        if (checkIsAdmin(conn)) {
            accountinfo.isAdmin = true;
        } else {
            accountinfo.isAdmin = false;
        }
        identifyCollectors(conn);
    }
}

  // ------ TEMPORARY ------

// It prints the name of all the collectors associated with the logged in user
void Account::identifyCollectors(std::shared_ptr<sql::Connection> conn) {

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