#include "databaseService.hpp"
#include <cstddef>
#include <mariadb/conncpp/Exception.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/SQLString.hpp>
#include <memory>
#include <stdexcept>
#include <string>

void DatabaseService::connectToDB(){
    // Lock the mutex for the duration of this function
    std::lock_guard<std::mutex> lock(dbMutex);

    std::ifstream configFile("config copy.json");
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

std::string DatabaseService::fetchPasswordHash(const std::string& firstName, const std::string& lastName) {
    // Lock the mutex for the duration of this function
    std::lock_guard<std::mutex> lock(dbMutex);
    
    try {
        // prepare statement
        auto stmt = std::unique_ptr<sql::PreparedStatement>
            (conn -> prepareStatement("SELECT PASSWORD FROM USERS WHERE FIRSTNAME = ? AND LASTNAME = ?"));
        stmt -> setString(1, firstName);
        stmt -> setString(2, lastName);


        auto res = std::unique_ptr<sql::ResultSet>(stmt -> executeQuery());
        if(res->next()) {
            
            sql::SQLString hash = res->getString("PASSWORD");        
            return std::string(hash);

        } 
    } catch(sql::SQLException& e) {
        std::cout << "SQL error" << e.what() << std::endl;
    }

    return "NO HASH!";
};


bool DatabaseService::fetchAdminStatus(const std::string& firstName, const std::string& lastName) {

    // Lock the mutex for the duration of this function
    std::lock_guard<std::mutex> lock(dbMutex);

    try {
        auto stmt = std::unique_ptr<sql::PreparedStatement> (conn -> prepareStatement("SELECT ISADMIn FROM USERS WHERE FIRSTNAME = ? AND LASTNAME = ?"));
        stmt -> setString(1, firstName);
        stmt -> setString(2, lastName);

        auto res = std::unique_ptr<sql::ResultSet>(stmt -> executeQuery());
        if(res->next()) {
            if (res->getBoolean("isAdmin")) {
                return true;
            } 
        } 
    } catch (sql::SQLException &e) {
        std::cout << "SQL error: " << e.what()<< std::endl;
    }
    return false;
}

std::string DatabaseService::fetchUserID(const std::string& firstName, const std::string& lastName) {

    // Lock the mutex for the duration of this function
    std::lock_guard<std::mutex> lock(dbMutex);

    try {
        auto stmt = std::unique_ptr<sql::PreparedStatement> (conn -> prepareStatement("SELECT USERID FROM USERS WHERE FIRSTNAME = ? AND LASTNAME = ?"));
        stmt -> setString(1, firstName);
        stmt -> setString(2, lastName);
    
        auto res = std::unique_ptr<sql::ResultSet>(stmt -> executeQuery());
        if(res->next()) {
            sql::SQLString id = res->getString("USERID");
            return std::string(id);
        }

    } catch (sql::SQLException &e) {
        std::cout << "SQL error: " << e.what()<< std::endl;
    }

    return "";
}