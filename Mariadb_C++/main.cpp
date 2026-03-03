#include <iostream>
#include <string>
#include <optional>
#include <mariadb/conncpp.hpp>

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

// Global connection pointer (simple style)
sql::Connection* connectDB(const DBSetup& dbSetup) {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();

        std::string url =
            "jdbc:mariadb://" +
            dbSetup.host + ":" +
            std::to_string(dbSetup.port) + "/" +
            dbSetup.database;

        sql::Connection* conn =
            driver->connect(url, dbSetup.user, dbSetup.password);

        std::cout << "Connection Success!\n";
        return conn;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Connection failed: " << e.what() << "\n";
        return nullptr;
    }
}

std::optional<int> loginUser(sql::Connection* conn, const UserInfo& userInfo) {
    try {
        sql::PreparedStatement* stmt =
            conn->prepareStatement(
                "SELECT AdminID, Password FROM admins WHERE FirstName = ? AND LastName = ?"
            );

        stmt->setString(1, userInfo.firstname);
        stmt->setString(2, userInfo.lastname);

        sql::ResultSet* res = stmt->executeQuery();

        if (!res->next()) {
            std::cout << "User not found\n";
            delete res;
            delete stmt;
            return std::nullopt;
        }

        int adminID = res->getInt("AdminID");
        std::string dbPassword = static_cast<std::string>(res->getString("Password"));

        delete res;
        delete stmt;

        if (userInfo.password == dbPassword) {
            std::cout << "Login Success! UserID: " << adminID << "\n";
            return adminID;
        } else {
            std::cout << "Incorrect password\n";
            return std::nullopt;
        }
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Login query failed: " << e.what() << "\n";
        return std::nullopt;
    }
}

int main() {
    DBSetup dbSetup;
    UserInfo user;

    std::cout << "Enter Firstname: ";
    std::getline(std::cin, user.firstname);

    std::cout << "Enter Lastname: ";
    std::getline(std::cin, user.lastname);

    std::cout << "Enter Password: ";
    std::getline(std::cin, user.password);

    sql::Connection* conn = connectDB(dbSetup);

    if (!conn) {
        return 1;
    }

    auto userID = loginUser(conn, user);

    if (userID) {
        std::cout << "User ID: " << *userID << " logged in.\n";
    } else {
        std::cout << "Login failed.\n";
    }

    delete conn;
    return 0;
}
