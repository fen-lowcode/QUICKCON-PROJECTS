#include <iostream>
#include <string>
#include <memory>
#include <optional>
#include <mariadb/conncpp.hpp> // Make sure mariadb-connector-cpp is installed

struct DBSetup {
    std::string host = "127.0.0.1";
    std::string user = "quickcon_admin";
    std::string password = "rvm152112databasE";
    std::string database = "quickcon_data";
    unsigned int port = 3306;
};

struct UserInfo {
    std::string firstname;
    std::string lastname;
    std::string password;
};

class Database {
private:
    std::shared_ptr<sql::Connection> conn;

public:
    Database(const DBSetup& dbSetup) {
        try {
            sql::Driver* driver = sql::mariadb::get_driver_instance();
            conn = std::shared_ptr<sql::Connection>(
                driver->connect(
                    "jdbc:mariadb://" + dbSetup.host + ":" + std::to_string(dbSetup.port) + "/" + dbSetup.database,
                    dbSetup.user,
                    dbSetup.password
                )
            );
            std::cout << "Connection Success!\n";
        } catch (const sql::SQLException& e) {
            std::cerr << "Connection failed: " << e.what() << "\n";
            exit(EXIT_FAILURE);
        }
    }

    // Login function: returns user ID on success
    std::optional<int> loginUser(const UserInfo& userInfo) {
        try {
            auto stmt = std::unique_ptr<sql::PreparedStatement>(
                conn->prepareStatement(
                    "SELECT AdminID, Password FROM admins WHERE FirstName = ? AND LastName = ?"
                )
            );
            stmt->setString(1, userInfo.firstname);
            stmt->setString(2, userInfo.lastname);

            auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery());

            if (!res->next()) {
                std::cout << "User not found\n";
                return std::nullopt;
            }

            int adminID = res->getInt("AdminID");
            std::string dbPassword = static_cast<std::string>(res->getString("Password"));

            if (userInfo.password == dbPassword) {
                std::cout << "Login Success! UserID: " << adminID << "\n";
                return adminID;
            } else {
                std::cout << "Incorrect password\n";
                return std::nullopt;
            }
        } catch (const sql::SQLException& e) {
            std::cerr << "Login query failed: " << e.what() << "\n";
            return std::nullopt;
        }
    }
};

int main() {
    DBSetup dbSetup;
    UserInfo user;

    std::cout << "Enter Firstname: ";
    std::getline(std::cin, user.firstname);
    std::cout << "Enter Lastname: ";
    std::getline(std::cin, user.lastname);
    std::cout << "Enter Password: ";
    std::getline(std::cin, user.password);

    Database db(dbSetup);
    auto userID = db.loginUser(user);

    if (userID) {
        std::cout << "User ID: " << *userID << " logged in.\n";
    } else {
        std::cout << "Login failed.\n";
    }

    return 0;
}