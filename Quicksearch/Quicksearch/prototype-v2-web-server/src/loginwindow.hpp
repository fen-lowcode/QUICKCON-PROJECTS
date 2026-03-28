#pragma once

#include <memory>
#include <wx/wx.h>
#include <wx/image.h>
#include <iostream>
#include <string>

#include <httplib.h>
#include <nlohmann/json.hpp>

#include "user.hpp"
#include "logs.hpp"

class LoginWindow : public wxFrame {
public:
    LoginWindow(std::shared_ptr<spdlog::logger> FILE_LOG ,const std::string& title);

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
};
