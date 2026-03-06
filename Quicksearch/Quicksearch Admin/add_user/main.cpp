#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Exception.hpp>
#include <mariadb/conncpp/SQLString.hpp>
#include <iomanip>
#include <sodium.h>
#include <iostream>
#include <string>
#include <mariadb/conncpp.hpp>
#include <sodium/crypto_hash_sha256.h>

class Adduser {

protected:

    std::string firstname {};
    std::string lastname {};
    bool isAdmin {false};

    std::string password;

    void inputUsername();
    bool setPriveleges();
    bool inputPassword(std::string & passBuf);
    void hashPassword(const std::string & passBuf);

public:
   
    bool createAccount();
};

bool Adduser::setPriveleges() {

    std::string response;

    std::cout << "Is this accout admin? y/n: "; std::getline(std::cin, response);
    
    if (response == "y") {
        std::cout << "Account set to Admin" << std::endl;
        isAdmin = true;
        return true;
    } else {
         std::cout << "Account not set to Admin" << std::endl;
         return false;
    }
}

bool Adduser::createAccount() {

    std::string passBuf;
    inputUsername();
    if (inputPassword(passBuf)) {
        hashPassword(passBuf);
        setPriveleges();
        std::cout << "Account successfully created: not yet added to database" << std::endl;
        return true;
    }

    return false;
}

// void Adduser::hashPassword(std::string& passBuf) {
//     crypto_hash_sha256(password, (const unsigned char*) passBuf.c_str(), passBuf.size());
//     std::cout << "Password hashed with SHA256" << std::endl;
// }

// ---------------------------------------------------- TEMPORARY TEST FIELD

void Adduser::hashPassword(const std::string& passBuf) {

    unsigned char hash[crypto_hash_sha256_BYTES];

    // hashes the password in the buffer into sha256 and place it in a temporary sha256 buffer
    crypto_hash_sha256(hash, (const unsigned char *)passBuf.c_str(), passBuf.size());

    std::stringstream ss;

    // Converts each bytes of the sha256 hash into an integer and then into it's hex character set to two bytes
    for (int i = 0; i < crypto_hash_sha256_BYTES; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    // after the loop converrsion above it then stores it as a string object
    password = ss.str();
}


// -----------------------------------------------------------------

void Adduser::inputUsername() {

    std::cout << "Enter new accout firstname: "; std::getline(std::cin, firstname);
    std::cout << "Enter new account lastname: "; std::getline(std::cin, lastname);
        
};

bool Adduser::inputPassword(std::string& passBuf) {
    std::string conPassBuf;
    std::cout << "Enter password for " << firstname << " " << lastname << std::endl;
    std::cout << "Password: "; std::getline(std::cin, passBuf);
    std::cout << "Confirm Password: "; std::getline(std::cin, conPassBuf);

    if (passBuf != conPassBuf) {
        std::cerr << "Paassword don't match";
        return false;
    }

    return true;
}



class Database : public Adduser {

private:

    std::string host = "127.0.0.1";
    std::string user = "fen";
    std::string userpassword = "1234";
    std::string database = "test";
    unsigned int port = 3306;

public:
    sql::Connection * conToDb() {
        try {

            // Instantiate Driver
            sql::Driver* driver = sql::mariadb::get_driver_instance(); 

            std::string url = "jdbc:mariadb://" + host + ":" + std::to_string(port) + "/" + database;
            sql::Connection * conn {driver->connect(url, user, userpassword)};
            std::cout << "Connection Success!\n";
            return conn;
        }

        catch(sql::SQLException& e) {
            std::cout << "SQL Error: " << e.what() << std::endl;
            exit(1);
        };
    }

    void insertNewusertoDB(sql::Connection * conn) {

        try {
            sql::PreparedStatement* stmt = conn -> prepareStatement("INSERT INTO users(FIRSTNAME, LASTNAME, PASSWORD, ISADMIN) value (?, ?, ?, ?)");
            stmt -> setString(1, firstname);
            stmt -> setString(2, lastname);
            stmt -> setString(3, password);
            stmt -> setBoolean(4, isAdmin);
            stmt -> executeUpdate();
            std::cout << "Successfully added new account to database!\n";
        } catch (sql::SQLException& e) {
            std::cout << "SQL Error: " << e.what() << std::endl;
            exit(1);
        }
    }
};


int main() {

    Database db;

    sql::Connection * conn = db.conToDb();
    if (db.createAccount()) {
        db.insertNewusertoDB(conn);
    } else {
        std::cerr << "Procedure Failure: Adding new account failed" << std::endl;
    }

    return 0;
}