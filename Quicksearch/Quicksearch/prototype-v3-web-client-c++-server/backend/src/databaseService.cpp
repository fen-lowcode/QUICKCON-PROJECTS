#include "databaseService.hpp"
// #include <cstddef>
#include <iostream>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Exception.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/SQLString.hpp>
#include <memory>
// #include <stdexcept>
#include <string>

void DatabaseService::connectToDB(){
    // Lock the mutex for the duration of this function
    std::lock_guard<std::mutex> lock(dbMutex);

    std::string host;
    std::string port;
    std::string user;
    std::string password;
    std::string database;

    try {
        std::ifstream configFile("dbconfig_local.json");
        nlohmann::json config; configFile >> config;

        host = config.at("host");
        port = config.at("port");
        user = config.at("user");
        password = config.at("password");
        database = config.at("database");

    } catch (nlohmann::json::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    };
    
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

nlohmann::json DatabaseService::fetchCustomerData() {
    std::lock_guard<std::mutex> lock(dbMutex);
    nlohmann::json customerList = nlohmann::json::array(); // Initialize as an array

    try {
        auto stmt = std::unique_ptr<sql::PreparedStatement>(
            conn->prepareStatement("SELECT * FROM CUSTOMER_RECORDS")
        );
    
        auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery());
        
        while (res->next()) {
            nlohmann::json customer;

            // Mapping SQL columns to JSON keys
            customer["ID"]              = res->getInt("ID");
            customer["CLIENTS_NAME"]    = std::string(res->getString("CLIENTS_NAME"));
            customer["CREDENTIALS"]     = std::string(res->getString("CREDENTIALS"));
            customer["ADDRESS"]         = std::string(res->getString("ADDRESS"));
            customer["PLAN"]            = std::string(res->getString("PLAN"));
            customer["DATE_APPLIED"]    = std::string(res->getString("DATE_APPLIED"));
            customer["CONTACT_NO"]      = std::string(res->getString("CONTACT_NO"));
            customer["AGE"]             = std::string(res->getString("AGE"));
            customer["SEX"]             = std::string(res->getString("SEX"));
            customer["SOCIAL_MEDIA"]    = std::string(res->getString("SOCIAL_MEDIA"));
            customer["OCCUPATION"]      = std::string(res->getString("OCCUPATION"));
            customer["DATE_OF_BIRTH"]   = std::string(res->getString("DATE_OF_BIRTH"));
            customer["PLACE_OF_BIRTH"]  = std::string(res->getString("PLACE_OF_BIRTH"));
            customer["OPTICAL_INFO"]    = std::string(res->getString("OPTICAL_INFO"));
            customer["SC_CONNECTOR"]    = std::string(res->getString("SC_CONNECTOR"));
            customer["FIBER_DROP"]      = std::string(res->getString("FIBER_DROP"));
            customer["TAPPING_CLIP"]    = std::string(res->getString("TAPPING_CLIP"));
            customer["CABLE_TIE"]       = std::string(res->getString("CABLE_TIE"));
            customer["F_CLAMP"]         = std::string(res->getString("F_CLAMP"));
            customer["REMARKS"]         = std::string(res->getString("REMARKS"));
            customer["INSTALLED_BY"]    = std::string(res->getString("INSTALLED_BY"));

            customerList.push_back(customer);
        }

    } catch (sql::SQLException &e) {
        std::cerr << "Database Fetching Data List Error: " << e.what() << std::endl;
        return nlohmann::json::object({{"error", e.what()}});
    }

    return customerList;
}

bool DatabaseService::RemoveCustomer(const std::string& userID) {
    std::lock_guard<std::mutex> lock(dbMutex);
    try {
        auto stmt = std::unique_ptr<sql::PreparedStatement> (this -> conn->prepareStatement("DELETE FROM CUSTOMER_RECORDS WHERE ID = ?"));
        stmt -> setInt(1, std::stoi(userID));

        int rowsAffected = stmt->executeUpdate();

        if(rowsAffected > 0) {
            return true;        // customer data with the unique ID is successfully deleted
        } else {
            return false;       // customer data with the unique ID is NOT FOUND
        }

    } catch(sql::SQLException& e) {
        std::cerr << "Database Customer Deletion Error: " << e.what() << std::endl;
        return false;
    }
}