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

class DatabaseService {

private:

    std::unique_ptr<sql::Connection> conn;

public:
    void connectToDB();
    bool checkCredentials(const std::string firstName, const std::string lastName,  const std::string password);
    bool checkPrivilage();
};