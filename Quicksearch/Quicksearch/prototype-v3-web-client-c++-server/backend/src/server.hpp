#pragma once

#include "accountHandler.hpp"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <nlohmann/json.hpp>

#include <string>
#include <httplib.h>
#include "tokenService.hpp"

class Server {

public:

    Server(AccountHandler& ah_) : accounthandler(ah_)
    {
        this -> serverHandler.new_task_queue = [] {return new httplib::ThreadPool(8); };
    }

    void optionReqHandler();
    void loginReqHandler();
    void customerDataHandler();
    void listen(const std::string host, int port);

private:

    AccountHandler& accounthandler;

    // httplib::SSLServer server("ssl/cert.pem", "ssl/key.pem");
    httplib::Server serverHandler;
};