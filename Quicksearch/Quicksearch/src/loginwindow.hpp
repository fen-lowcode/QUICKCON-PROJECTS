#pragma once

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
    LoginWindow(const std::string& title, std::shared_ptr<User>);

private:

    std::shared_ptr<User> user;
    std::shared_ptr<wxTextCtrl> firstnameBox;
    std::shared_ptr<wxTextCtrl> lastnameBox;
    std::shared_ptr<wxTextCtrl> passwordBox;
    std::shared_ptr<wxButton> btnEnter;

    wxString firstnameBoxPlaceHol {"Firstname"};
    wxString lastnameBoxPlaceHol {"Lastname"};
    wxString passwordBoxPlaceHol {"Password"};
    bool isClosing {false};

    void setTextBoxPlacehol(wxTextCtrl* textbox,const wxString placeHolder, const bool isClosing);
    void setPasswordPlacehol(wxTextCtrl* textbox, const wxString& placeHolderconst, const bool isClosing);
    std::string hashPassword(std::string passBuffer);

    void btnEvents();
    void initializeLogin(wxCommandEvent& event);
};
