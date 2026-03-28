CXX = ccache g++
CXXFLAGS = -O3 -std=c++17 -fPIE -pipe `wx-config --cxxflags` -I/usr/local/include
LDFLAGS = `wx-config --libs` -L/usr/local/lib/mariadb
LIBS = -lmariadbcpp -lsodium -lspdlog -lfmt

SRC = src/loginwindow.cpp \
    src/dashboard.cpp \
    src/user.cpp \
    src/main.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
