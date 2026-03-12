#pragma once

#include <memory>
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