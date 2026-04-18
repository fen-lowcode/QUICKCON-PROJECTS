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
            customer["id"]              = res->getInt("ID");
            customer["name"]            = std::string(res->getString("CLIENTS_NAME"));
            customer["credentials"]     = std::string(res->getString("CREDENTIALS"));
            customer["address"]         = std::string(res->getString("ADDRESS"));
            customer["plan"]            = std::string(res->getString("PLAN"));
            customer["date_applied"]    = std::string(res->getString("DATE_APPLIED"));
            customer["contact_no"]      = std::string(res->getString("CONTACT_NO"));
            customer["age"]             = std::string(res->getString("AGE"));
            customer["sex"]             = std::string(res->getString("SEX"));
            customer["social_media"]    = std::string(res->getString("SOCIAL_MEDIA"));
            customer["occupation"]      = std::string(res->getString("OCCUPATION"));
            customer["dob"]             = std::string(res->getString("DATE_OF_BIRTH"));
            customer["pob"]             = std::string(res->getString("PLACE_OF_BIRTH"));
            customer["optical_info"]    = std::string(res->getString("OPTICAL_INFO"));
            customer["sc_connector"]    = std::string(res->getString("SC_CONNECTOR"));
            customer["fiber_drop"]      = std::string(res->getString("FIBER_DROP"));
            customer["tapping_clip"]    = std::string(res->getString("TAPPING_CLIP"));
            customer["cable_tie"]       = std::string(res->getString("CABLE_TIE"));
            customer["f_clamp"]         = std::string(res->getString("F_CLAMP"));
            customer["remarks"]         = std::string(res->getString("REMARKS"));
            customer["installed_by"]    = std::string(res->getString("INSTALLED_BY"));

            customerList.push_back(customer);
        }

    } catch (sql::SQLException &e) {
        std::cerr << "Database Error: " << e.what() << std::endl;
        return nlohmann::json::object({{"error", e.what()}});
    }

    return customerList;
}