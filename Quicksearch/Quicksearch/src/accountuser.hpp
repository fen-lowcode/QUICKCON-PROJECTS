#pragma once

#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <sodium/crypto_hash_sha256.h>
#include <wx/wx.h>
#include <sodium.h>
#include <mariadb/conncpp.hpp>

class Account {

private:

    struct DBCredentials {
        std::string host;
        std::string user;
        std::string userpassword;
        std::string database;
        unsigned int port;
    }; struct DBCredentials dbcredentials;
   
    struct accountInfo {

        int userID;
        bool isAdmin;

    }; struct accountInfo accountinfo;

public:

    // conncting to Database

    sql::Connection * connToDB();
    // verify user crendentials
    bool autheticateLogin(const std::string& firstname,const std::string& lastname,const std::string& password);    
    bool checkIsAdmin();        // this checks if the verified user is an admin
    
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
    void login(std::string& firstname, std::string& lastname, std::string& password);
};