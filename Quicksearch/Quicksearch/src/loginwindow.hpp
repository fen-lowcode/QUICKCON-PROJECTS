#pragma once

#include <wx/wx.h>
#include <wx/image.h>
#include "accountuser.hpp"
#include <sodium.h>

#define LOGO "./assets/quick_search_logo.png"

class LoginWindow : public wxFrame, public User {
public:
    LoginWindow(const std::string& title);

private:
    wxTextCtrl* firstnameBox;
    wxTextCtrl* lastnameBox;
    wxTextCtrl* passwordBox;

    wxString firstnameBoxPlaceHol {"Firstname"};
    wxString lastnameBoxPlaceHol {"Lastname"};
    wxString passwordBoxPlaceHol {"Password"};
    bool isClosing {false};

    void setTextBoxPlacehol(wxTextCtrl* textbox,const wxString placeHolder, const bool isClosing);
    void setPasswordPlacehol(wxTextCtrl* textbox, const wxString& placeHolderconst, const bool isClosing);
    void sendInput(wxCommandEvent& event);

    void hashPassword(std::string passBuffer);
};
