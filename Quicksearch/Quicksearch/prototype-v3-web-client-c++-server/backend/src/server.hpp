#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include <nlohmann/json.hpp>
#include <httplib.h>


class Server {

public:


    void requestHandlers() {
        serverHandler.Options(R"(.*)", [](const httplib::Request& req, httplib::Response& res) {
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type");
            res.status = 204; // "No Content" - tells the browser it's okay to proceed
        });

        serverHandler.Post("/auth/session", [=](const httplib::Request& req, httplib::Response& res){

            // signal the browser to take input
            res.set_header("Access-Control-Allow-Origin", "*");

            try {
                nlohmann::json dataHandler = nlohmann::json::parse(req.body);
                std::string firstname = dataHandler.at("fname");
                std::string lastname = dataHandler.at("lname");
                std::string password = dataHandler.at("psw");

                std::cout << firstname << lastname << password << std::endl;
        
                res.status = 200;
                res.set_content("{\"status\":\"success\"}", "application/json");

                

            } catch(nlohmann::json::parse_error& ex) {
                res.status = 415;
                res.reason = "Unsupported Media type";
            }
        });
    }

    void listen(const std::string host, int port) {
        serverHandler.listen(host , port);
    }

private:
    // httplib::SSLServer server("ssl/cert.pem", "ssl/key.pem");
    httplib::Server serverHandler;


};