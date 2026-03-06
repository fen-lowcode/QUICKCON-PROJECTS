#pragma once

#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <sodium/crypto_hash_sha256.h>
#include <wx/wx.h>
#include <sodium.h>
#include <mariadb/conncpp.hpp>
#include "databaseconnect.hpp"

class Account : public DatabaseConnect{

protected:

    struct accountInfo {

        int userID;
        bool isAdmin;

    }; struct accountInfo accountinfo;

public:
    // verify user crendentials
    bool autheticateLogin(std::shared_ptr<sql::Connection> conn, const std::string& firstname,const std::string& lastname,const std::string& password);    
    
    
    bool checkIsAdmin(std::shared_ptr<sql::Connection> conn);        // this checks if the verified user is an admin 
    // this updates the account status to isActive = true in the database 
    // purpose: for preventing an account to have multiple sessions
    bool updateAccessState();
};

class User : public Account{

protected:
    std::string firstname;
    std::string lastname;
    std::string password;

public:
    void useProgram(std::string& firstname, std::string& lastname, std::string& password);
};