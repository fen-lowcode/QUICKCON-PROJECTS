#pragma once

#include <sodium/crypto_hash_sha256.h>
#include <wx/wx.h>
#include <sodium.h>


class Account {

private:
   
    struct accountInfo {

        int userID;
        bool isAdmin;

    }; struct accountInfo accountinfo;

public:
    bool autheticateLogin();     // verify user crendentials before loog in
    bool checkIsAdmin();        // this checks if the verified user is an admin
    
    // this updates the account status to isActive = true in the database 
    // purpose: for preventing an account to have multiple sessions
    bool autheticateAccess();
};

class User : public Account{

protected:
    std::string firstname;
    std::string lastname;
    unsigned char password[crypto_hash_sha256_BYTES];

public:
    void login(std::string_view firstname, std::string_view lastname, unsigned char password[]);
};