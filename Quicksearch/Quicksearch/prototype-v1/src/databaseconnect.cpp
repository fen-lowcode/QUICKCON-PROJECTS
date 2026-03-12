
#include "databaseconnect.hpp"

#define HOST "192.168.1.16"
#define USER "quicksearch"
#define UPASSWORD "G=]&I[v;k!gbegi(PLQh"
#define DATABASE "quickcon_data"
#define PORT 3306

DatabaseConnect::DatabaseConnect(std::shared_ptr<spdlog::logger> FILE_LOG) {
    this -> FILE_LOG = FILE_LOG;
}

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
        LOGINFO(FILE_LOG, "Database connection established");
        return conn;
    }

    catch(sql::SQLException& e) {
        LOGFATAL(FILE_LOG, "Database connection not established");
        std::cout << "SQL Error: " << e.what() << std::endl;
        exit(1);
    };
}

