#pragma once
#include <mutex>
#include "mariadb/conncpp.hpp"
#include <fstream>
#include <iostream>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Exception.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <sodium.h>


class DatabaseService {

private:

    std::unique_ptr<sql::Connection> conn;
    std::mutex dbMutex; // The "Gatekeeper" for your database connection

public:
    void connectToDB();
    std::string fetchPasswordHash(const std::string& firstName, const std::string& lastName);
    std::string fetchUserID(const std::string& firstName, const std::string& lastName);

    bool fetchAdminStatus(const std::string& firstName, const std::string& lastName);
    nlohmann::json fetchCustomerData();
};

