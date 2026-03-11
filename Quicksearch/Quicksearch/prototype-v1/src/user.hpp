#pragma once

#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <memory>
#include <sodium/crypto_hash_sha256.h>
#include <wx/wx.h>
#include <sodium.h>
#include <mariadb/conncpp.hpp>
#include <thread>

#include "account.hpp"




class User : public Account{

private:
    std::string firstname;
    std::string lastname;
    std::string password;

public:

    User(std::shared_ptr<spdlog::logger> FILE_LOG, std::shared_ptr<sql::Connection> conn);


    void setUsername(std::string firstname, std::string lastname);
    void setPassword(std::string password);
    std::string getFirstName();
    std::string getLastName();
    std::string getPassword();

    std::string fetchUsername();
    bool login();
};