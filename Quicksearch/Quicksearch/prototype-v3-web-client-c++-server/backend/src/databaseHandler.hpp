#pragma once
#include "mariadb/conncpp.hpp"
#include <fstream>
#include <iostream>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Exception.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

class DatabaseHandler {

private:

    static std::unique_ptr<sql::Connection> conn;

public:
    void connectToDB(){
        std::ifstream configFile("config.json");
        nlohmann::json config; configFile >> config;

        std::string host = config.at("host");
        std::string port = config.at("port");
        std::string user = config.at("user");
        std::string password = config.at("password");
        std::string database = config.at("database");
        
        try {
            sql::Driver* driver = sql::mariadb::get_driver_instance();
            std::string databaseUrl= "jdbc:mariadb://" + host + ":" + port + "/" + database;

            conn.reset(driver->connect(databaseUrl, user, password));
            std::cout << "Now connected to " << host << ":" << port << " at database " << database << std::endl;

        } catch (sql::SQLException& e) {
            std::cerr << "Database handler: " << e.what() << std::endl;
        }

    }

    static bool checkUserFromDB(const std::string username, const std::string password) {

        try {
            // prepare statement
            auto stmt = std::unique_ptr<sql::PreparedStatement>(conn -> prepareStatement("SELECT PASSWORD FROM USERS WHERE FIRSTNAME=?"));
            stmt -> setString(1, username);

            // executre and 
            auto res = std::unique_ptr<sql::ResultSet>(stmt -> executeQuery());
            if(res->next()) {
                
                if (password != res->getString("password")){
                    return false;
                }
                
                return true;
            } 
        } catch(sql::SQLException& e) {
            std::cout << "SQL error" << e.what() << std::endl;
        }
        return false;
    };
};