#include "accountuser.hpp"

void User::login(std::string_view firstname, std::string_view lastname, unsigned char password[]) {
    std::cout << firstname << " " << lastname << std::endl;
    std::cout << "Password is ";
    std::cout << password << std::endl;
}
