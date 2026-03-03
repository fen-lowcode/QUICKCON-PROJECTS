#include <wx/wx.h>
#include <wx/version.h>

class MyFrame : public wxFrame {
public:
    MyFrame(const std::string& title);

private:
    
};

MyFrame::MyFrame(const std::string& title)
    : wxFrame(nullptr, wxID_ANY, title)
{
     // Panel (always use a panel for controls)
    wxPanel* panel = new wxPanel(this);

    // Text box
    wxTextCtrl* firstname = new wxTextCtrl(panel, wxID_ANY, "",
                                           wxPoint(20, 20), wxSize(200, 30));

    // Button
    wxButton* button = new wxButton(panel, wxID_ANY, "Click Me",
                                     wxPoint(20, 70), wxSize(100, 30));

    // Bind button click event (modern way)
    button->Bind(wxEVT_BUTTON, [](wxCommandEvent&) {
        wxMessageBox("Button Clicked!", "Info");
    });
}


class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        MyFrame *frame = new MyFrame("My wxWidgets App");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);