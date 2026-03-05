
#include <wx/wx.h>
#include "loginwindow.hpp"


class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        LoginWindow* frame = new LoginWindow("Welcome to Quicksearch");
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);