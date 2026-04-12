#include "databaseService.hpp"

void DatabaseService::connectToDB(){
    std::ifstream configFile("config.json");
    nlohmann::json config; configFile >> config;

    std::string host = config.at("host");
    std::string port = config.at("port");
    std::string user = config.at("user");
    std::string password = config.at("password");
    std::string database = config.at("database");
    
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        std::string databaseUrl= "jdbc:mariadb://" + host + ":" + port + "/" + database;

        conn.reset(driver->connect(databaseUrl, user, password));
        std::cout << "Now connected to " << host << ":" << port << " at database " << database << std::endl;

    } catch (sql::SQLException& e) {
        std::cerr << "Database handler: " << e.what() << std::endl;
    }

}

bool DatabaseService::checkCredentials(const std::string firstName, const std::string lastName,  const std::string password) {

    try {
        // prepare statement
        auto stmt = std::unique_ptr<sql::PreparedStatement>
            (conn -> prepareStatement("SELECT PASSWORD FROM USERS WHERE FIRSTNAME = ? AND LASTNAME = ?"));
        stmt -> setString(1, firstName);
        stmt -> setString(2, lastName);

        // executre and 
        auto res = std::unique_ptr<sql::ResultSet>(stmt -> executeQuery());
        if(res->next()) {
            
            if (password != res->getString("password")){
                return false;
            }
            
            return true;
        } 
    } catch(sql::SQLException& e) {
        std::cout << "SQL error" << e.what() << std::endl;
    }
    return false;
};


