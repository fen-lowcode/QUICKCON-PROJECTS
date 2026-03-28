#pragma once

#include <memory>
#include "logs.hpp"



class User {

private:
    std::string firstname;
    std::string lastname;
    std::string password;

public:

    User(std::shared_ptr<spdlog::logger> FILE_LOG);


    void setUsername(std::string firstname, std::string lastname);
    void setPassword(std::string password);

    std::string getFirstName();
    std::string getLastName();
    std::string getPassword();

    std::string fetchUsername();
    bool login();
};