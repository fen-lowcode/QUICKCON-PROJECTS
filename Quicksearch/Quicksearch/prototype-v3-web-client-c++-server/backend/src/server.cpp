#include "server.hpp"


void Server::optionReqHandler() {                                             
    serverHandler.Options(R"(.*)", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 204; // "No Content" - tells the browser it's okay to proceed
    });
}

void Server::loginReqHandler() {

    serverHandler.Post("/auth/session", [this](const httplib::Request& req, httplib::Response& res){

        // signal the browser to take input
        res.set_header("Access-Control-Allow-Origin", "*");

        // checks if the body payload is a valid json format
        if(!nlohmann::json::accept(std::string(req.body))) {
            res.status = 400;
            res.set_content("{\"status\":\"Invalid Request\"}", "application/json");
        }

            // parses the body from request and takes data in the json body,
            // throws an exception and catches it if a json field is missing

            try {
                nlohmann::json dataHandler = nlohmann::json::parse(req.body);
                std::string firstName = dataHandler.at("fname");
                std::string lastName = dataHandler.at("lname");
                std::string password = dataHandler.at("psw");

                std::cout << " User: " << firstName << " " << lastName << " attepmted to log in" << std::endl;

                // check if login is valid or not
                std::string token = accounthandler.accountAuth(firstName, lastName, password);
                if (!token.empty()) {

                    res.status = 200;
                    res.set_content("{\"token\":\"" + token + "\"}", "application/json");
    
                } else {
                    res.status = 401;
                    res.set_content("{\"status\":\"failed\"}", "application/json");
                }
    
            } catch(std::exception& e) {
                res.status = 415;
                res.reason = "Unsupported Media type";
            }

        } 
    );
}

void Server::listen(const std::string host, int port) {
    serverHandler.listen(host , port);
}
