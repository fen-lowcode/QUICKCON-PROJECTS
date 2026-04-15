#pragma once 
#include "databaseService.hpp"
#include "tokenService.hpp"
#include <sodium.h>

class AccountHandler {

public:

    AccountHandler(DatabaseService& databaseServ_ , TokenService& tokenServ_) 
    : databaseServ(databaseServ_), tokenServ{tokenServ_} 
    {}

    std::string accountAuth(  const std::string& firstName, const std::string& lastName, const std::string& password );

private:

    DatabaseService& databaseServ;
    TokenService& tokenServ;

};