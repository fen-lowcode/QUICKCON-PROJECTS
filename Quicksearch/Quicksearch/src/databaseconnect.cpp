
#include "databaseconnect.hpp"
#include <mariadb/conncpp/Connection.hpp>
#include <memory>

#define HOST "127.0.0.1"
#define USER "fen"
#define UPASSWORD "1234"
#define DATABASE "test"
#define PORT 3306

std::shared_ptr<sql::Connection> DatabaseConnect::connToDB() {
    dbcredentials.host = HOST;
    dbcredentials.user = USER;
    dbcredentials.userpassword = UPASSWORD;
    dbcredentials.database = DATABASE;
    dbcredentials.port = PORT;

    try {
        // Instantiate Driver
        sql::Driver* driver = sql::mariadb::get_driver_instance(); 

        std::string url = 
        "jdbc:mariadb://" + dbcredentials.host + ":" + std::to_string(dbcredentials.port) + "/" + dbcredentials.database;
        std::shared_ptr<sql::Connection> conn (driver->connect(url, dbcredentials.user, dbcredentials.userpassword));
        std::cout << "Database: Connection Success!\n";
        return conn;
    }

    catch(sql::SQLException& e) {
        std::cout << "SQL Error: " << e.what() << std::endl;
        exit(1);
    };
}

