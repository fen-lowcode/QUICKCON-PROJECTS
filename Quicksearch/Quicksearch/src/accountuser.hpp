#pragma once

#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <memory>
#include <sodium/crypto_hash_sha256.h>
#include <wx/wx.h>
#include <sodium.h>
#include <mariadb/conncpp.hpp>



class Account {

protected:

    std::shared_ptr<sql::Connection> conn;

    struct accountInfo {

        int userID;
        bool isAdmin;

    }; struct accountInfo accountinfo;

public:

    Account(std::shared_ptr<sql::Connection> conn) {
        this -> conn = conn;
    };

    // verify user crendentials
    bool autheticateLogin( const std::string& firstname,const std::string& lastname,const std::string& password);    
    
    
    bool checkIsAdmin();        // this checks if the verified user is an admin 
    // this updates the account status to isActive = true in the database 
    // purpose: for preventing an account to have multiple sessions
    bool updateAccessState();

    // ------ TEMPORARY ------
    void identifyCollectors();
};



class User : public Account{

private:
    std::string firstname;
    std::string lastname;
    std::string password;
public:

    User(std::shared_ptr<sql::Connection> conn) : Account(conn) {}
    void setUsername(std::string firstname, std::string lastname);
    void setPassword(std::string password);
    std::string fetchUsername();
    bool login();
};