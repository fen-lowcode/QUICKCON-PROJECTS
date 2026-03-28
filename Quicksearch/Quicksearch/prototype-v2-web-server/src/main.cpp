#include <memory>
#include <wx/wx.h>

#include "user.hpp"
#include "loginwindow.hpp"
#include "logs.hpp"
#include <iostream>

auto FILE_LOG = initLog();

class MyApp : public wxApp {
public:
    virtual bool OnInit() override {

    
        auto user = std::make_shared<User>;
        LoginWindow* loginWindow = new LoginWindow(FILE_LOG, "Welcome to Quicksearch");
        loginWindow -> Show();

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);