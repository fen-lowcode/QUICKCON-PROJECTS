#include "accountuser.hpp"
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Exception.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <mariadb/conncpp/SQLString.hpp>

#define HOST "127.0.0.1"
#define USER "fen"
#define UPASSWORD "1234"
#define DATABASE "test"
#define PORT 3306

sql::Connection * Account::connToDB() {
    
    dbcredentials.host = HOST;
    dbcredentials.user = USER;
    dbcredentials.userpassword = UPASSWORD;
    dbcredentials.database = DATABASE;
    dbcredentials.port = PORT;

    try {
        // Instantiate Driver
        sql::Driver* driver = sql::mariadb::get_driver_instance(); 

        std::string url = 
            "jdbc:mariadb://" + 
            dbcredentials.host + 
            ":" + 
            std::to_string(dbcredentials.port) + 
            "/" + 
            dbcredentials.database;

        sql::Connection * conn {driver->connect(url, dbcredentials.user, dbcredentials.userpassword)};
        std::cout << "Connection Success!\n";
        return conn;
    }

    catch(sql::SQLException& e) {
        std::cout << "SQL Error: " << e.what() << std::endl;
        exit(1);
    };
}


// refactor this SHIT!!
bool Account::autheticateLogin(const std::string& firstname,const std::string& lastname,const std::string& password) {

    // connect to db
    sql::Connection* conn = connToDB();
    
    try{
        sql::PreparedStatement * stmt  = conn -> 
        prepareStatement("SELECT PASSWORD FROM users WHERE FIRSTNAME = ? AND LASTNAME = ?");
        stmt -> setString(1, firstname);
        stmt -> setString(2, lastname);

        sql::ResultSet * res = stmt -> executeQuery();
        if (res->next()) {  // move to first row
            sql::SQLString passwordFromDB = res->getString("PASSWORD");

            if(password == passwordFromDB) {
                stmt = conn ->  prepareStatement("SELECT USERID FROM users WHERE FIRSTNAME = ? AND LASTNAME = ?");
                stmt -> setString(1, firstname);
                stmt -> setString(2, lastname);
                sql::ResultSet * res2 = stmt -> executeQuery();
                    if (res2->next()) {
                        accountinfo.userID = res2->getInt("userID"); 
                        std::cout << "Welcome! User " << accountinfo.userID << std::endl;
                    }

                    return true;
            } else {
                std::cout << "Password dont match\n";
            }
        }


    } catch (sql::SQLException& e) {
        std::cout << "SQL error: " << e.what() << std::endl;
    }

    delete conn;
    return false;
}


void User::login(std::string& firstname, std::string& lastname, std::string& password) {

    std::cout << firstname << " " << lastname << std::endl;
    std::cout << "Password is ";
    std::cout << password << std::endl;

    autheticateLogin(firstname, lastname, password);
}
