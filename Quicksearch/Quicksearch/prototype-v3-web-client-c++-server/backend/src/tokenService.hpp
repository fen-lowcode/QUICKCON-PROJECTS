#pragma once

#include <chrono>
#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/kazuho-picojson/defaults.h>


class TokenService {

public:
    std::string createToken(const std::string& userId, const std::string userRole, const std::string& issuer, const std::string secretKey) {

        auto token = jwt::create()
        .set_issuer(issuer)
        .set_type("JWS")
        .set_payload_claim("user_id", jwt::claim(userId))
        .set_payload_claim("role", jwt::claim(userRole))
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes(15))
        .sign(jwt::algorithm::hs256{secretKey});

        return token;
    }

};