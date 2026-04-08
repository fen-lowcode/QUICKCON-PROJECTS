#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include <nlohmann/json.hpp>
#include <httplib.h>


class Server {

public:


    void optionReqHandler() {
        serverHandler.Options(R"(.*)", [](const httplib::Request& req, httplib::Response& res) {
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type");
            res.status = 204; // "No Content" - tells the browser it's okay to proceed
        });
    }

    void loginReqHandler(bool(*checkUserFromDB)(const std::string username,const  std::string password)) {

        serverHandler.Post("/auth/session", [=](const httplib::Request& req, httplib::Response& res){

            // signal the browser to take input
            res.set_header("Access-Control-Allow-Origin", "*");

            try {
                nlohmann::json dataHandler = nlohmann::json::parse(req.body);
                std::string username = dataHandler.at("uname");
                std::string password = dataHandler.at("psw");

                std::cout << " User: " << username << " has logged in with password " << password << std::endl;
                if (checkUserFromDB(username, password) == true) {
                    res.status = 200;
                    res.set_content("{\"status\":\"success\"}", "application/json");
                } else {
                    res.status = 401;
                    res.set_content("{\"status\":\"failed\"}", "application/json");
                }
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