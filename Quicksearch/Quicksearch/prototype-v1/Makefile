make:
	g++ src/main.cpp src/user.cpp src/account.cpp src/loginwindow.cpp src/databaseconnect.cpp \
	src/dashboard.cpp src/logs.cpp -o app `wx-config --cxxflags --libs` -lsodium \
	-I/usr/local/include -L/usr/local/lib/mariadb -lmariadbcpp -lspdlog -lfmt -O0
