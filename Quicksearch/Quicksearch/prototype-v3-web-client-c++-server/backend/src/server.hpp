#include "databaseService.hpp"
#include <exception>
#include <string>
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include <nlohmann/json.hpp>
#include <sodium.h>
#include <httplib.h>
#include "tokenService.hpp"

class Server {

public:

    Server(DatabaseService& databaseService, TokenService& tokenService): databaseService(databaseService), tokenService{tokenService} 
    {
        this -> serverHandler.new_task_queue = [] {return new httplib::ThreadPool(8); };
    }

    void optionReqHandler();
    void loginReqHandler();
    void listen(const std::string host, int port);

private:

    DatabaseService& databaseService;
    TokenService& tokenService;

    // httplib::SSLServer server("ssl/cert.pem", "ssl/key.pem");
    httplib::Server serverHandler;
};