#pragma once

#include <iostream>
#include <memory>
#include <mariadb/conncpp.hpp>
#include "logs.hpp"

class DatabaseConnect {

private:
    std::shared_ptr<spdlog::logger> FILE_LOG;

public:
 // mov this out
    struct DBCredentials {
        std::string host;
        std::string user;
        std::string userpassword;
        std::string database;
        unsigned int port;
    }; struct DBCredentials dbcredentials;

    DatabaseConnect(std::shared_ptr<spdlog::logger> FILE_LOG);
    std::shared_ptr<sql::Connection>connToDB();
};
