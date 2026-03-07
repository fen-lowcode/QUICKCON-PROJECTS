#pragma once

#include <memory>
#include <wx/wx.h>
#include <wx/image.h>
#include "accountuser.hpp"
#include <sodium.h>
#include "dashboard.hpp"

#define LOGO "./assets/quick_search_logo.png"

class LoginWindow : public wxFrame {
public:
    LoginWindow(const std::string& title, std::shared_ptr<User>);

private:

    std::shared_ptr<User> user;
    wxTextCtrl* firstnameBox;
    wxTextCtrl* lastnameBox;
    wxTextCtrl* passwordBox;

    wxString firstnameBoxPlaceHol {"Firstname"};
    wxString lastnameBoxPlaceHol {"Lastname"};
    wxString passwordBoxPlaceHol {"Password"};
    bool isClosing {false};

    void setTextBoxPlacehol(wxTextCtrl* textbox,const wxString placeHolder, const bool isClosing);
    void setPasswordPlacehol(wxTextCtrl* textbox, const wxString& placeHolderconst, const bool isClosing);
    std::string hashPassword(std::string passBuffer);
    void initializeLogin(wxCommandEvent& event);
};
