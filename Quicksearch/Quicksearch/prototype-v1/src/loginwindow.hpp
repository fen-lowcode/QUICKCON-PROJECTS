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

    wxPanel* panel {nullptr};
    wxBoxSizer* mainSizer {nullptr};
    wxBoxSizer* userNameSizer {nullptr};
    wxStaticBitmap* logo {nullptr};

    wxTextCtrl* firstnameBox {nullptr};
    wxTextCtrl* lastnameBox {nullptr};
    wxTextCtrl* passwordBox {nullptr};
    wxButton* btnEnter {nullptr};

    bool isClosing {false};

    void setUpLogo();
    void setUpInputBoxes();
    void setupLayout();
    void btnEvents();
    void initializeLogin(wxCommandEvent& event);
};
