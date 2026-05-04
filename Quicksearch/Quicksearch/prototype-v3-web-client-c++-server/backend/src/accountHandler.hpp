#pragma once 
#include "databaseService.hpp"
#include "tokenService.hpp"
#include <nlohmann/json_fwd.hpp>
#include <sodium.h>

class AccountHandler {

public:

    AccountHandler(DatabaseService& databaseServ_ , TokenService& tokenServ_) 
    : databaseServ(databaseServ_), tokenServ{tokenServ_} 
    {
        this -> extractSecrets();
    }

    std::string         accountAuth(  const std::string& firstName, const std::string& lastName, const std::string& password );
    bool                vrfyJwtToken(std::string token);
    nlohmann::json      getCustomerData();
    nlohmann::json      getCustomerHistory(const std::string& ID);
    bool                deleteCustomer(const nlohmann::json& JSONreq);
    bool                addCustomer(const nlohmann::json& JSONreq);
    bool                updateCustomer(const nlohmann::json& JSONreq);
    bool                addPaymentHistory(const nlohmann::json& JSONreq);


private:

    std::string secretKey;
    std::string issuer;

    std::mutex mutexGuard;

    DatabaseService& databaseServ;
    TokenService& tokenServ;

    // Gets the secret key for calculating hash from the external json file (secretkey.json)
    void extractSecrets();


};