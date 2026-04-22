#include "server.hpp"
#include <iterator>
#define DATA_PROTECTION

void Server::optionReqHandler() {                                             
    serverHandler.Options(R"(.*)", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 204; // "No Content" - tells the browser it's okay to proceed
    });
}

// checks if http request body is a valid json file
auto reqIsJson = [](const httplib::Request& req, httplib::Response& res) {
    if(!nlohmann::json::accept(std::string(req.body))) {
        res.status = 400;
        res.set_content("{\"status\":\"Invalid Request\"}", "application/json");
        return false;
    }
    return true;
};

void Server::loginReqHandler() {

    serverHandler.Post("/auth/session", [this](const httplib::Request& req, httplib::Response& res){

        // signal the browser to take input
        res.set_header("Access-Control-Allow-Origin", "*");
        if(!reqIsJson(req, res)) {return;}

            // parses the body from request and takes data in the json body,
            // throws an exception and catches it if a json field is missing

            try {
                nlohmann::json reqToJson = nlohmann::json::parse(req.body);
                std::string firstName = reqToJson.at("fname");
                std::string lastName = reqToJson.at("lname");
                std::string password = reqToJson.at("psw");

                std::cout << " User: " << firstName << " " << lastName << " attepmted to log in" << std::endl;

                // check if login is valid or not
                std::string token = accounthandler.accountAuth(firstName, lastName, password);
                if (!token.empty()) {

                    res.status = 200;
                    res.set_content("{\"token\":\"" + token + "\"}", "application/json");
    
                } else {
                    res.status = 401;
                    res.set_content("{\"reply\":\"login failure\"}", "application/json");
                }
    
            } catch(std::exception& e) {
                res.status = 415;
                res.reason = "Unsupported Media type";
            }

        } 
    );
}

void Server::customerListReqHandler() {
    serverHandler.Post("/get/customerlist", [this](const httplib::Request& req, httplib::Response& res) {

          // signal the browser to take input
        res.set_header("Access-Control-Allow-Origin", "*");
        if(!reqIsJson(req, res)) {return;}

        nlohmann::json JSONreq = nlohmann::json::parse(req.body);

        #ifdef DATA_PROTECTION
        if (!accounthandler.vrfyJwtToken(JSONreq.at("token"))) {
            res.status = 401;
            res.set_content("{\"reply\":\"You Are Not Allowed To Do That\"}", "application/json");
            std::cout << " REQUEST REFUSED " << std::endl; 
            return;
        }
        #endif


        std::cout << " REQUEST ACCEPTED " << std::endl; 
        res.set_content(accounthandler.getCustomerData().dump(), "application/json");


    });
}

void Server::deleteCustomerReq() {
    serverHandler.Post("/delete/customerinfo", [this](const httplib::Request& req, httplib::Response& res){

        res.set_header("Access-Control-Allow-Origin", "*");
        if(!reqIsJson(req, res)) {return;}

        nlohmann::json JSONreq = nlohmann::json::parse(req.body);
    
        #ifdef DATA_PROTECTION
        if (!accounthandler.vrfyJwtToken(JSONreq.at("token"))) {
            res.status = 401;
            res.set_content("{\"reply\":\"You Are Not Allowed To Do That\"}", "application/json");
            std::cout << " REQUEST REFUSED " << std::endl; 
            return;
        }
        #endif 

        if (accounthandler.deleteCustomerData(JSONreq.at("customerToDel"))){

            res.set_content("{\"reply\": \"Customer Data Deleted\"}", "application/json");

        } else {
    
            res.status = 500;
            res.set_content("{\"reply\": \"Customer Data Not Deleted\"}", "application/json");
        }

    });
}

void Server::listen(const std::string host, int port) {
    serverHandler.listen(host , port);
}

