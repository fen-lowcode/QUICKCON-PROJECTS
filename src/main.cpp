#include <cstdlib>
#include <mysql/mysql.h>
#include <iostream>
#include <string.h>
#include <cstddef>

#define SUCCESS 0

struct SQLQueries {

    std::string loginQuery {"SELECT Password FROM admins WHERE FirstName = ? AND LastName = ?"};
    std::string getuserIDQuery {"SELECT AdminID from admins where Firstname = ? and Lastname = ?"};

}; SQLQueries sqlQueries;

struct UserInfo{

    std::string userid;
    std::string firstname;
    std::string lastname;
    std::string password;

};

struct DBSetup{
    std::string host {"127.0.0.1"};
    std::string username {"quickcon_admin"};
    std::string password {"rvm152112databasE"};
    int port {3306};
    std::string db {"quickcon_data"};
};  

int connectToDb(MYSQL * conn, DBSetup * dbsetup) {

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

// A function that takes an input for the database password
void inputDatabsePassword(std::string * password) {
    std::cout << "Enter database Password: "; std::getline(std::cin, *password);
}

void inputLoginCredentials(struct UserInfo * userinfo) {
    std::cout << "Enter Firstname: "; std::getline(std::cin, userinfo->firstname);
    std::cout << "Enter Lastname: ";  std::getline(std::cin, userinfo->lastname);
    std::cout << "Password: ";        std::getline(std::cin, userinfo->password);
}


int getUserID(MYSQL_STMT * stmt, UserInfo * userinfo) {


   return 1;
}

MYSQL_STMT * prepareLoginReq(MYSQL_STMT * stmt, struct UserInfo * userinfo) {
    
    // “Hey database, is this query structurally valid and ready to run later?”
    if (mysql_stmt_prepare(stmt, sqlQueries.loginQuery.c_str(), sqlQueries.loginQuery.size())) {
        std::cout << "Prepare error: " << mysql_stmt_error(stmt) << std::endl;
        exit(EXIT_FAILURE);
    }

    static MYSQL_BIND bind_login_credentials[2];
    memset(bind_login_credentials,0, sizeof(bind_login_credentials));
    
    // Prepares and defines the input username arguments to be included into sql query
    bind_login_credentials[0].buffer_type = MYSQL_TYPE_STRING;
    bind_login_credentials[0].buffer = (void*)userinfo -> firstname.c_str();
    bind_login_credentials[0].buffer_length = userinfo -> firstname.size();

    bind_login_credentials[1].buffer_type = MYSQL_TYPE_STRING;
    bind_login_credentials[1].buffer = (void*)userinfo -> lastname.c_str();
    bind_login_credentials[1].buffer_length = userinfo -> lastname.size();

    // Bind the sql query and the arguments
    mysql_stmt_bind_param(stmt, bind_login_credentials);

    return stmt;
}

void sendAndGetLoginRes(MYSQL_STMT *stmt, UserInfo * userInfo) {

    if (mysql_stmt_execute(stmt)) {
        std::cout << "Login: Query  Execution Failed ";
        exit(EXIT_FAILURE);
    }

    char passBuffer[255];
    memset(passBuffer, 0, sizeof(passBuffer));

    unsigned long passwordLength = 0;
    my_bool is_null = 0;

    MYSQL_BIND result[1];
    memset(result, 0, sizeof(result));

    // Defining the memory map region to mariadb
    
    result[0].buffer_type = MYSQL_TYPE_STRING;      // What datatype this memory region is
    result[0].buffer = passBuffer;                  // The actual region where mariadb will write into
    result[0].buffer_length = sizeof(passBuffer);   // The size of the buffer
    result[0].length = &passwordLength;             // It will me modified by maria to put the actual data
    result[0].is_null = &is_null;                   // Mariadb writes here if the result is none or not

    // Intwhereructs maria on where to put the result in memory // no execution yet only mapping first
    mysql_stmt_bind_result(stmt, result);
    mysql_stmt_store_result(stmt);

    
    // checks if fetching the result succeed
    if (mysql_stmt_fetch(stmt) == 0) {
        if(is_null) {
           std::cout << "Query: No output";
           exit(EXIT_FAILURE);
        }

        if (userInfo->password == passBuffer) {
            std::cout << "login: Success";
        } else if (userInfo -> password != passBuffer) {
            std::cerr << "Login: failure";
        }
    }  
}



int main() {

    struct UserInfo userInfo;
    struct DBSetup dbSetup;
    
    // Initialize mysql API
    MYSQL * conn = mysql_init(NULL);

     // Prepare stmt to point on query statements // This stmt pointer can point to different queries
    MYSQL_STMT * stmt = mysql_stmt_init(conn);

    // Connemysql/mariadb Database with login credentials and specify database name
    //inputDatabsePassword(&dbSetup.password);
    connectToDb(conn, &dbSetup);
    inputLoginCredentials(&userInfo);

    sendAndGetLoginRes(prepareLoginReq(stmt, &userInfo), & userInfo);


    // Don't forget to close connection of the database and stmt sock
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return 0;
}
