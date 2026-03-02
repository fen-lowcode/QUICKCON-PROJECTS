#include "wx/chartype.h"
#include "wx/event.h"
#include "wx/generic/statusbr.h"
#include "wx/version.h"
#include <wx/wx.h>
#include <iostream>

class MyFrame : public wxFrame {
    public:
        MyFrame(std::string title);

        void onAbout(wxCommandEvent& event) {
            wxString msg;
            msg.Printf(wxT("Hello and welcome to %s"), wxVERSION_STRING);
        }

        void onQuit(wxCommandEvent& event) {
            Close();
        }

    private:
        DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame);
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout);
EVT_MENU(wxID_EXIT, MyFrame::OnQuit);
END_EVENT_TABLE();


class MyApp : public wxApp {

public:
    virtual bool onInit(
    );
};
