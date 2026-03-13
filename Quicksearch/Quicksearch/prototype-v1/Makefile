CXX = ccache g++
CXXFLAGS = -O3 -std=c++17 -pipe `wx-config --cxxflags` -I/usr/local/include
LDFLAGS = `wx-config --libs` -L/usr/local/lib/mariadb
LIBS = -lmariadbcpp -lsodium -lspdlog -lfmt

SRC = src/main.cpp \
    src/user.cpp \
    src/account.cpp \
    src/loginwindow.cpp \
    src/databaseconnect.cpp \
    src/dashboard.cpp \
    src/adminpanel.cpp \
    src/userconfigwindow.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)