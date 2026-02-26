#include <mariadb/conncpp.hpp>
#include <iostream>
#include <string>

struct UserInfo {
    int userid;
    std::string firstname;
    std::string lastname;
    std::string password;
};

int main() {
    std::string url = "jdbc:mariadb://127.0.0.1:3306/quickcon_data";
    std::string user = "quickcon_admin";
    std::string db_password = "rvm152112databasE";

    try {
        // Create a connection
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        std::unique_ptr<sql::Connection> conn(driver->connect(url, user, db_password));

        std::cout << "Connected to database!\n";

        // Input login credentials
        UserInfo userInfo;
        std::cout << "Enter Firstname: "; std::getline(std::cin, userInfo.firstname);
        std::cout << "Enter Lastname: ";  std::getline(std::cin, userInfo.lastname);
        std::cout << "Enter Password: ";  std::getline(std::cin, userInfo.password);

        // Prepare statement for login
        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(
                "SELECT AdminID, Password FROM admins WHERE Firstname = ? AND Lastname = ?"
            )
        );

        stmt->setString(1, userInfo.firstname);
        stmt->setString(2, userInfo.lastname);

        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());

        if (res->next()) {
            int adminID = res->getInt("AdminID");
            std::string dbPassword = res->getString("Password");

            if (dbPassword == userInfo.password) {
                std::cout << "Login success! AdminID: " << adminID << "\n";
                userInfo.userid = adminID;
            } else {
                std::cerr << "Login failed: wrong password.\n";
            }
        } else {
            std::cerr << "Login failed: user not found.\n";
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error: " << e.what() 
                  << " (MySQL error code: " << e.getErrorCode() 
                  << ", SQLState: " << e.getSQLState() << ")\n";
    }

    return 0;
}