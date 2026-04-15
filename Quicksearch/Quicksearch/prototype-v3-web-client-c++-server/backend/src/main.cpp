#include "accountHandler.hpp"
#include "server.hpp"
#include "databaseService.hpp"
#include "tokenService.hpp"


int main() {

    DatabaseService databaseService;
    TokenService tokenService;

    databaseService.connectToDB();

    AccountHandler accountHandler(databaseService, tokenService);
    Server server(accountHandler);

    server.optionReqHandler();
    server.loginReqHandler();

    server.listen("0.0.0.0", 2222);
}