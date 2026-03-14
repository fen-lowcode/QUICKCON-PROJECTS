#pragma once

#include <mariadb/conncpp/Connection.hpp>
#include <memory>
#include <wx/wx.h>
#include <wx/image.h>
#include "user.hpp"
#include <iomanip>
#include <memory>
#include "dashboard.hpp"
#include "logs.hpp"
#include "adminpanel.hpp"

class LoginWindow : public wxFrame {
public:
    LoginWindow(std::shared_ptr<spdlog::logger> FILE_LOG ,const std::string& title, std::shared_ptr<User> user);

private:
    std::shared_ptr<User> user;
    std::shared_ptr<spdlog::logger> FILE_LOG;

    wxPanel* panel;
    wxBoxSizer* mainSizer;
    wxBoxSizer* userNameSizer;
    wxStaticBitmap* logo;

    wxTextCtrl* firstnameBox;
    wxTextCtrl* lastnameBox;
    wxTextCtrl* passwordBox;
    wxButton* btnEnter;

    bool isClosing {false};
    
    std::string hashPassword(std::string passBuffer);

    void setUpLogo();
    void setUpInputBoxes();
    void setupLayout();
    void btnEvents();
    void initializeLogin(wxCommandEvent& event);
};
