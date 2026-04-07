#include "server.hpp"
#include "databaseHandler.hpp"

int main() {
    Server server;
    server.requestHandlers();
    server.listen("0.0.0.0", 2222);

}