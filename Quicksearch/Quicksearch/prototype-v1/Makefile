make:
	g++ src/main.cpp src/user.cpp src/account.cpp src/loginwindow.cpp src/databaseconnect.cpp \
	src/dashboard.cpp src/adminpanel.cpp -o app `wx-config --cxxflags --libs` -lsodium \
	-I/usr/local/include -L/usr/local/lib/mariadb -lmariadbcpp -lspdlog -lfmt -O3
