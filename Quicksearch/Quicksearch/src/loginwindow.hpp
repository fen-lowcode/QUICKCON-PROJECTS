#pragma once

#include <mariadb/conncpp/Connection.hpp>
#include <memory>
#include <wx/wx.h>
#include <wx/image.h>
#include "accountuser.hpp"
#include <iomanip>
#include <memory>
#include "dashboard.hpp"


#define LOGO "./assets/quick_search_logo.png"

class LoginWindow : public wxFrame {
public:
    LoginWindow(const std::string& title, std::shared_ptr<User> user);

private:

    std::shared_ptr<User> user;
    std::shared_ptr<wxTextCtrl> firstnameBox;
    std::shared_ptr<wxTextCtrl> lastnameBox;
    std::shared_ptr<wxTextCtrl> passwordBox;
    std::shared_ptr<wxButton> btnEnter;

    bool isClosing {false};
    
    std::string hashPassword(std::string passBuffer);

    void btnEvents();
    void initializeLogin(wxCommandEvent& event);
};
