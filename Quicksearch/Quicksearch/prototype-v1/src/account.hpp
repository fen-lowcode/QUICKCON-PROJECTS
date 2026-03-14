#include <wx/wx.h>
#include <memory>
#include <mariadb/conncpp.hpp>
#include <sodium.h>
#include <thread>
#include <chrono>
#include "logs.hpp"
#include "sstream"

class Account {

protected:

    std::shared_ptr<spdlog::logger> FILE_LOG;
    std::shared_ptr<sql::Connection> conn;

    struct accountInfo {

        int userID;
        bool isAdmin;

    }; struct accountInfo accountinfo;

public:

    Account(std::shared_ptr<spdlog::logger>  FILE_LOG, std::shared_ptr<sql::Connection> conn) {
        this -> FILE_LOG = FILE_LOG;
        this -> conn = conn;
    };

    std::shared_ptr<sql::Connection> getConnection();

    // verify user crendentials
    bool autheticateLogin( const std::string& firstname,const std::string& lastname,const std::string& password);  

    // this checks if the verified user is an admin 
    bool checkIsAdmin();   

    // this updates the account status lastsen to rcent tim 30 sc interval  purpose: for preventing an account to have multiple sessions
    void updateActiveStatus();

    // check the active status of a user
    bool checkActiveStatus(std::string firstname, std::string lastname, std::string password);


    void updateUserConfiguration(int userID, std::string firstname, std::string lastname, bool isAdmin);
};

