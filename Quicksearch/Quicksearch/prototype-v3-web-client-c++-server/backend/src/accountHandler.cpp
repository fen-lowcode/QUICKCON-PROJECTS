#include "accountHandler.hpp"
#include "databaseService.hpp"
#include <exception>
#include <fstream>
#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/kazuho-picojson/traits.h>
#include <mariadb/conncpp/Exception.hpp>
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

bool AccountHandler::addCustomer(const nlohmann::json& JSONreq) {
    std::lock_guard<std::mutex> lock(this -> mutexGuard);

    try {

            bool success = databaseServ.AddCustomer(
                JSONreq.at("CLIENTS_NAME"),
                JSONreq.at("CREDENTIALS"),
                JSONreq.at("ADDRESS"),
                JSONreq.at("PLAN"),
                JSONreq.at("DATE_APPLIED"),
                JSONreq.at("CONTACT_NO"),
                JSONreq.at("AGE"),
                JSONreq.at("SEX"),
                JSONreq.at("SOCIAL_MEDIA"),
                JSONreq.at("OCCUPATION"),
                JSONreq.at("DATE_OF_BIRTH"),
                JSONreq.at("PLACE_OF_BIRTH"),
                JSONreq.at("OPTICAL_INFO"),
                JSONreq.at("SC_CONNECTOR"),
                JSONreq.at("FIBER_DROP"),
                JSONreq.at("TAPPING_CLIP"),
                JSONreq.at("CABLE_TIE"),
                JSONreq.at("F_CLAMP"),
                JSONreq.at("REMARKS"),
                JSONreq.at("INSTALLED_BY")
            );

            std::cout << "yehey new customer  " << std::endl;
            std::cout << "        " << std::endl;
            std::cout << "  (\\ /)" << std::endl;
            std::cout << "  ( . .)" << std::endl;
            std::cout << "  c(\")(\")" << std::endl;
            std::cout << "      " << std::endl;

            if(success) {return true;};

    }  catch (nlohmann::json::exception& e) {
        std::cout << "JSON ERROR MISSING KEY: " << e.what() << std::endl;
        std::cout << JSONreq.at("CLIENTS_NAME") << " Customer is not deleted" << std::endl;
        return false;
    }

    std::cout << JSONreq.at("CLIENTS_NAME") << " Customer is not deleted" << std::endl;
    return false;
}

bool AccountHandler::deleteCustomer(const nlohmann::json& JSONreq) {

    std::lock_guard<std::mutex> lock(this -> mutexGuard);

    try {
         // checks if every key in the JSONreq that are curcial is existing before sending to database handler to delete the data

        [[maybe_unused]] nlohmann::json checker = {
            {"ID",      JSONreq.at("ID")},
            {"CLIENTS_NAME",    JSONreq.at("CLIENTS_NAME")},
            {"CREDENTIALS",   JSONreq.at("CREDENTIALS")},
        };  
    
    std::cout << JSONreq.at("CLIENTS_NAME") << " Data Will be Deleted" << std::endl;
    return databaseServ.RemoveCustomer(JSONreq.at("ID"));


    } catch (nlohmann::json::exception& e) {
        std::cout << "JSON ERROR MISSING KEY: " << e.what() << std::endl;
        std::cout << JSONreq.at("CLIENTS_NAME") << " Data Info NOT Deleted" << std::endl;
        return false;
    }
}


bool AccountHandler::updateCustomer(const nlohmann::json& JSONreq) {

    try {

    databaseServ.updateCustomer(
        JSONreq.at("ID").get<std::string>(),
            JSONreq.at("CLIENTS_NAME").get<std::string>(),
            JSONreq.at("CREDENTIALS").get<std::string>(),
            JSONreq.at("ADDRESS").get<std::string>(),
            JSONreq.at("PLAN").get<std::string>(),
            JSONreq.at("DATE_APPLIED").get<std::string>(),
            JSONreq.at("CONTACT_NO").get<std::string>(),
            JSONreq.at("AGE").get<std::string>(),
            JSONreq.at("SEX").get<std::string>(),
            JSONreq.at("SOCIAL_MEDIA").get<std::string>(),
            JSONreq.at("OCCUPATION").get<std::string>(),
            JSONreq.at("DATE_OF_BIRTH").get<std::string>(),
            JSONreq.at("PLACE_OF_BIRTH").get<std::string>(),
            JSONreq.at("OPTICAL_INFO").get<std::string>(),
            JSONreq.at("SC_CONNECTOR").get<std::string>(),
            JSONreq.at("FIBER_DROP").get<std::string>(),
            JSONreq.at("TAPPING_CLIP").get<std::string>(),
            JSONreq.at("CABLE_TIE").get<std::string>(),
            JSONreq.at("F_CLAMP").get<std::string>(),
            JSONreq.at("REMARKS").get<std::string>(),
            JSONreq.at("INSTALLED_BY").get<std::string>()
        );
        return true;

    } catch(nlohmann::json::exception& e) {
        std::cout << "JSON ERROR MISSING KEY: " << e.what() << std::endl;
        std::cout << JSONreq.at("CLIENTS_NAME") << " Data Info NOT Deleted" << std::endl;
        return false;
    }
    return false;
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
