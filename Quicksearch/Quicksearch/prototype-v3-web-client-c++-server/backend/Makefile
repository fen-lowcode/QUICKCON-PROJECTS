make:
	g++ src/main.cpp src/accountHandler.cpp src/server.cpp src/databaseService.cpp -o quicksearch_server \
    		-I /usr/local/include/mariadb \
    		-L /usr/local/lib/mariadb \
    		-lssl -lcrypto -lmariadbcpp -lsodium
