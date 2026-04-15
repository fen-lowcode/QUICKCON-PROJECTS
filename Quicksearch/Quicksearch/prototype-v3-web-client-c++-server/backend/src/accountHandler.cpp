#include "accountHandler.hpp"
#include <mutex>
#include <string>



auto hashPass = [](std::string pass) {
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

    if(hashPass(password) == databaseServ.fetchPasswordHash(firstName, lastName)) {

        std::string userID = databaseServ.fetchUserID(firstName, lastName);
        bool isAdmin = databaseServ.fetchAdminStatus(firstName, lastName);

        return tokenServ.createToken(userID, isAdmin == true? "admin": "user" , "123456789");
    } 

    return "";
}

nlohmann::json AccountHandler::getCustomerData() {
    return databaseServ.fetchCustomerData();
}