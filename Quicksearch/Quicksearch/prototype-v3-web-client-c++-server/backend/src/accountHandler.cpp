#include "accountHandler.hpp"
#include <exception>
#include <fstream>
#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/kazuho-picojson/traits.h>
#include <mutex>
#include <nlohmann/json_fwd.hpp>
#include <resolv.h>
#include <string>

inline auto hashPass = [](std::string pass) {

    unsigned char hash[crypto_hash_sha256_BYTES];
    crypto_hash_sha256(hash, (const unsigned char *)pass.c_str(), pass.size());
    std::stringstream ss;

    // Converts each bytes of the sha256 hash into an integer and then into it's hex character set to two bytes
    for (int i = 0; i < crypto_hash_sha256_BYTES; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    // after the loop converrsion above it then stores it as a string object
    return ss.str();
};


std::string AccountHandler::accountAuth(
    const std::string& firstName, const std::string& lastName, const std::string& password
) {

    std::lock_guard<std::mutex> lock(this -> mutexGuard);
    if(hashPass(password) == databaseServ.fetchPasswordHash(firstName, lastName)) {

        std::string userID = databaseServ.fetchUserID(firstName, lastName);
        bool isAdmin = databaseServ.fetchAdminStatus(firstName, lastName);

        return tokenServ.createToken(userID, isAdmin == true? "admin": "user" , this -> issuer, this -> secretKey);
    } 

    return "";
}

nlohmann::json AccountHandler::getCustomerData() {
    return databaseServ.fetchCustomerData();
}

bool AccountHandler::deleteCustomerData(const nlohmann::json& JSONreq) {

    std::lock_guard<std::mutex> lock(this -> mutexGuard);

    try {
         // checks if every key in the JSONreq that are curcial is existing before sending to database handler to delete the data

        nlohmann::json ({

            {"id",      JSONreq.at("id")},
            {"name",    JSONreq.at("name")},
            {"creds",   JSONreq.at("creds")},
        }
    );  
    
    std::cout << JSONreq.at("name") << " Data Will be Deleted" << std::endl;
    return databaseServ.RemoveCustomer(JSONreq.at("id"));


    } catch (nlohmann::json::exception& e) {
        std::cout << "JSON ERROR MISSING KEY: " << e.what() << std::endl;
        std::cout << JSONreq.at("name") << " Data Info NOT Deleted" << std::endl;
        return false;
    }
}


bool AccountHandler::vrfyJwtToken(std::string token) {

    std::lock_guard<std::mutex> lock(this -> mutexGuard);

    try {
        jwt::decoded_jwt<jwt::traits::kazuho_picojson> decodedToken = jwt::decode(token);
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256(this->secretKey)).with_issuer(this->issuer);
        verifier.verify(decodedToken);
        return true;

    } catch(std::exception& e) {
        std::cout << "Token: " << token << "INVALID TOKEN\n";
    }

    return false;
}

void AccountHandler::extractSecrets() {
    try {
        std::ifstream fileWithSecrets("secretkey.json");
        nlohmann::json varWithSecrets; fileWithSecrets >> varWithSecrets;

        this -> secretKey = varWithSecrets.at("secretKey");
        this -> issuer = varWithSecrets.at("issuer");

    } catch (nlohmann::json::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    };
}
