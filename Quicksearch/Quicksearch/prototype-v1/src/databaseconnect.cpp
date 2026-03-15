
#include "databaseconnect.hpp"
#include <fstream>


DatabaseConnect::DatabaseConnect(std::shared_ptr<spdlog::logger> FILE_LOG) {
    this -> FILE_LOG = FILE_LOG;
}

std::shared_ptr<sql::Connection> DatabaseConnect::connToDB() {

    std::stringstream logMessage;

    std::ifstream  dbConfigFile{"configdb.json"};
    nlohmann::json dbConfig; dbConfigFile >> dbConfig;

    dbcredentials.host = dbConfig["host"];
    dbcredentials.user = dbConfig["user"];
    dbcredentials.userpassword = dbConfig["password"];
    dbcredentials.database = dbConfig["database"];
    dbcredentials.port = dbConfig["port"];

    try {
        // Instantiate Driver
        sql::Driver* driver = sql::mariadb::get_driver_instance(); 
        std::string url = 
        "jdbc:mariadb://" + dbcredentials.host + ":" + std::to_string(dbcredentials.port) + "/" + dbcredentials.database;

        std::shared_ptr<sql::Connection> conn (driver->connect(url, dbcredentials.user, dbcredentials.userpassword));
        logMessage << "Database connection established on HOST: " << dbcredentials.host << " on PORT: " << dbcredentials.port;
        LOGINFO(FILE_LOG, logMessage.str());
        return conn;
    }

    catch(sql::SQLException& e) {
        logMessage << "Database connection NOT established on HOST: " << dbcredentials.host << " on PORT: " << dbcredentials.port << "SQL error: " << e.what();
        LOGFATAL(FILE_LOG, logMessage.str());
        exit(1);
    };
}

