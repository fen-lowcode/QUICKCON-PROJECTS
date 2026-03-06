
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/Connection.hpp>
#include <iostream>

class DatabaseConnect {
public:
 // mov this out
    struct DBCredentials {
        std::string host;
        std::string user;
        std::string userpassword;
        std::string database;
        unsigned int port;
    }; struct DBCredentials dbcredentials;

protected:
    std::shared_ptr<sql::Connection>connToDB();
};
