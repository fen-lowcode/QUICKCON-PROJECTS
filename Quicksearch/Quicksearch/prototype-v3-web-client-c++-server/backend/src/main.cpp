#include "server.hpp"
#include "databaseService.hpp"
#include "tokenService.hpp"


int main() {

    DatabaseService databaseService;
    TokenService tokenService;
    databaseService.connectToDB();

    Server server(databaseService, tokenService);

    server.optionReqHandler();
    server.loginReqHandler();

    server.listen("0.0.0.0", 2222);
}