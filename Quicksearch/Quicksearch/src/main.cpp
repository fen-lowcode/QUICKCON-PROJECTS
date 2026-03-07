#include <memory>
#include <wx/wx.h>
#include "accountuser.hpp"
#include "databaseconnect.hpp"
#include "loginwindow.hpp"



class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        
        std::shared_ptr<DatabaseConnect> db = std::make_shared<DatabaseConnect>();
        auto conn = db -> connToDB();
        auto user = std::make_shared<User>((conn));
        LoginWindow* loginWindow = new LoginWindow("Welcome to Quicksearch", user);
        loginWindow -> Show();

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);