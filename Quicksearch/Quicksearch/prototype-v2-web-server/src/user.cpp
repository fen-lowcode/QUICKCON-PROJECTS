
#include "user.hpp"

User::User(std::shared_ptr<spdlog::logger> FILE_LOG, std::shared_ptr<sql::Connection> conn) : Account(FILE_LOG, conn){}

void User::setUsername(std::string firstname, std::string lastname) {
    this -> firstname = firstname;
    this -> lastname = lastname;
}


void User::setPassword(std::string password) {
    this -> password = password;
}


bool User::login() {
    return autheticateLogin(
        this -> firstname, 
        this -> lastname, 
        this -> password
    );
}

// Getters

std::string User::fetchUsername() {
    auto convertToUpper = [](std::string username) -> std::string {
        for(char& c: username) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        return username;
    };

    std::string username = convertToUpper(this -> getFirstName() + " " + getLastName());
    return username;
}

std::string User::getFirstName() {
    return this -> firstname;
}


std::string User::getLastName() {
    return this -> lastname;
}

std::string User::getPassword() {
    return this -> password;
}


