#include <memory>
#include <wx/wx.h>
#include "user.hpp"
#include "databaseconnect.hpp"
#include "loginwindow.hpp"
#include "logs.hpp"
#include <iostream>

auto FILE_LOG = initLog();

class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        
        std::shared_ptr<DatabaseConnect> db = std::make_shared<DatabaseConnect>(FILE_LOG);
        auto conn = db -> connToDB();
    
        auto user = std::make_shared<User>(FILE_LOG, conn);
        LoginWindow* loginWindow = new LoginWindow("Welcome to Quicksearch", user);
        loginWindow -> Show();

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);