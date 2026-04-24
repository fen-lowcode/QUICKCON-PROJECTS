#pragma once
#include <mutex>
#include "mariadb/conncpp.hpp"
#include <fstream>
#include <iostream>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Exception.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <sodium.h>


class DatabaseService {

private:

    std::unique_ptr<sql::Connection> conn;
    std::mutex dbMutex; // The "Gatekeeper" for your database connection

public:
    void connectToDB();
    std::string     fetchPasswordHash(const std::string& firstName, const std::string& lastName);
    std::string     fetchUserID(const std::string& firstName, const std::string& lastName);

    bool            fetchAdminStatus(const std::string& firstName, const std::string& lastName);
    nlohmann::json  fetchCustomerData();

    bool            RemoveCustomer(const std::string& userID);
    bool            AddCustomer(
                        const std::string& CLIENTS_NAME,
                        const std::string& CREDENTIALS,
                        const std::string& ADDRESS,
                        const std::string& PLAN,
                        const std::string& DATE_APPLIED,
                        const std::string& CONTACT_NO,
                        const std::string& AGE,
                        const std::string& SEX,
                        const std::string& SOCIAL_MEDIA,
                        const std::string& OCCUPATION,
                        const std::string& DATE_OF_BIRTH,
                        const std::string& PLACE_OF_BIRTH,
                        const std::string& OPTICAL_INFO,
                        const std::string& SC_CONNECTOR,
                        const std::string& FIBER_DROP,
                        const std::string& TAPPING_CLIP,
                        const std::string& CABLE_TIE,
                        const std::string& F_CLAMP,
                        const std::string& REMARKS,
                        const std::string& INSTALLED_BY
                     );
};

