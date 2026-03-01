#include <iostream>
#include <string_view>


struct userAccountDatabase {

    int userID = 1;
    std::string firstname = "john";
    std::string lastname = "meryenda";
    std::string password = "sinigang";
    bool isAdmin = false;
};

struct userAccountDatabase uad;

class Accounts {

private:
    int userID;
    std::string password;
    bool isAdmin;

public:
    
    bool verifyLogin(std::string_view firstname, std::string_view lastname, std::string_view password) {

        if(uad.firstname != firstname || uad.lastname != lastname) {
            std::cerr << "User account not found\n";
        }

        if(uad.password ==  password) {
            return true;
        }
        return false;
    };

    int getUserID() {
        return uad.userID;
    };

    bool checkIsAdmin() {
        if (uad.isAdmin) {
            std::cout << "User is Admin\n";
            return true;
        } else {
            std::cout << "User is not Admin\n";
            return false;
        }
    }
};


class User : public Accounts {

private:
    std::string firstname;
    std::string lastname;
    std::string password;

public:

    void inputCredentials() {
        std::cout << "Firstname: "; std::getline(std::cin, firstname);
        std::cout << "Lastname: "; std::getline(std::cin, lastname);
        std::cout << "Password: "; std::getline(std::cin, password);
    }

    bool login() {
        if (verifyLogin(firstname, lastname, password)) {
            std::cout << "Login success\n";
            return true;
        } else {
            std::cout << "Login failed\n";
            return false;
        }
    }

};

int main() {

    User user;
    user.inputCredentials();

    if(user.login()) {
        user.getUserID();
        user.checkIsAdmin();
    }
    
    return 0;
}