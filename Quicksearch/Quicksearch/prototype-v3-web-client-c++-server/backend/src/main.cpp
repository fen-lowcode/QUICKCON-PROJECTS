#include "server.hpp"
#include "databaseHandler.hpp"

// THIS IS THE MISSING PIECE:
std::unique_ptr<sql::Connection> DatabaseHandler::conn = nullptr;

int main() {

    DatabaseHandler dbHandler;
    dbHandler.connectToDB();

    Server server;

    server.optionReqHandler();
    server.loginReqHandler(dbHandler.checkUserFromDB);

    server.listen("0.0.0.0", 2222);
}