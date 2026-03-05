
#include <wx/wx.h>
#include "loginwindow.hpp"


class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        LoginWindow* loginWindow = new LoginWindow("Welcome to Quicksearch");
        loginWindow -> Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);