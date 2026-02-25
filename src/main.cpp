#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <functional>

struct SQLQueries {

    std::string loginQuery = "SELECT Password FROM admins WHERE FirstName = ? AND LastName = ?";
};

struct UserInfo{
    std::string firstname;
    std::string lastname;
    std::string password;

};

struct DBSetup{
    std::string host = "127.0.0.1";
    std::string username = "fenen";
    std::string password = "qcupupust";
    int port = 3306;
    std::string db = "assigning_users_to_locations";
};  

int ConnToDb(MYSQL * conn, DBSetup * dbsetup) {

      if(!mysql_real_connect(
        conn,
        dbsetup->host.c_str(), 
        dbsetup->username.c_str(), 
        dbsetup->password.c_str(), 
        dbsetup->db.c_str(), 
        dbsetup->port,
        NULL, 
        0)
    ) {

        std::cerr << "Connection failure: " << mysql_error(conn) << "\n";
        mysql_close(conn);
        exit(1);
    }


    std::cout << "Connection Success!\n";
    return 0;
}

void LoginUser(struct UserInfo * userinfo) {
    std::cout << "Enter Firstname: "; std::getline(std::cin, userinfo->firstname);
    std::cout << "Enter Lastname: ";  std::getline(std::cin, userinfo->lastname);
    std::cout << "Password: ";        std::getline(std::cin, userinfo->password);
}

int main() {

    struct UserInfo userInfo;
    struct DBSetup dbSetup;
    
    MYSQL * conn = mysql_init(NULL);
    ConnToDb(conn, &dbSetup);
    LoginUser(&userInfo);

    std::cout << userInfo.firstname << std::endl;
    std::cout << userInfo.lastname << std::endl;
    std::cout << userInfo.password << std::endl;


    return 0;
}