// #include "wx/gtk/textctrl.h"
#include <wx/wx.h>

class LoginWindow : public wxFrame {

public:
    LoginWindow(std::string &title);

private:
    wxTextCtrl* firstnameBox;
    wxTextCtrl* lastnameBox;

    void OnLogin();
};

LoginWindow::LoginWindow(std::string &title) : 
wxFrame(nullptr, wxID_ANY, title,
        wxDefaultPosition,
        wxSize(500, 350),
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {

    this->Center();

    wxPanel* panel = new wxPanel(this);

    // Main vertical sizer (stack rows)
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->AddStretchSpacer(2);  // push everything to vertical center

    // --- First row: Firstname label + box ---
    wxBoxSizer* row1 = new wxBoxSizer(wxHORIZONTAL);
    // wxStaticText* firstnameLabel = new wxStaticText(panel, wxID_ANY, "FIRSTNAME");
    firstnameBox = new wxTextCtrl(panel, wxID_ANY, "John", wxDefaultPosition, wxSize(200,30));

      // remove placeholder when set focus
    firstnameBox->Bind(wxEVT_SET_FOCUS, [this](wxFocusEvent&) {
    if (firstnameBox->GetValue() == "Firstname") {
            firstnameBox->SetValue("");
            firstnameBox->SetForegroundColour(*wxLIGHT_GREY);
        } 
    });

    // Restore placeholder on losing focus
    firstnameBox->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent&) {
        if (firstnameBox->GetValue().IsEmpty()) {
            firstnameBox->SetValue("Firstname");
            firstnameBox->SetForegroundColour(*wxLIGHT_GREY);
        }
    });
    
    // row1->Add(firstnameLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10); // gap 10px

    row1->Add(firstnameBox, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(row1, 0, wxALIGN_CENTER | wxBOTTOM, 15); // center row, 15px below for spacing

    // --- Second row: Lastname label + box ---
    wxBoxSizer* row2 = new wxBoxSizer(wxHORIZONTAL);
    // wxStaticText* lastnameLabel = new wxStaticText(panel, wxID_ANY, "LASTNAME");
    lastnameBox = new wxTextCtrl(panel, wxID_ANY, "Smith", wxDefaultPosition, wxSize(200,30));

    // remove placeholder when set focus
    lastnameBox->Bind(wxEVT_SET_FOCUS, [this](wxFocusEvent&) {
    if (lastnameBox->GetValue() == "Lastname") {
            lastnameBox->SetValue("");
            lastnameBox->SetForegroundColour(*wxBLACK);
        }
    });

      // Restore placeholder on losing focus
    lastnameBox->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent&) {
        if (lastnameBox->GetValue().IsEmpty()) {
            lastnameBox->SetValue("Lastname");
            lastnameBox->SetForegroundColour(*wxLIGHT_GREY);
        }
    });
    


    // row2->Add(lastnameLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    row2->Add(lastnameBox, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(row2, 0, wxALIGN_CENTER);

    mainSizer->AddStretchSpacer(1);  // push everything to vertical center
    panel-> SetSizer(mainSizer);
}

class MyApp : public wxApp {

    virtual bool OnInit() override {

        std::string title = "Welcome to Quicksearch";
        LoginWindow *frame = new LoginWindow(title);
        frame->Show();
        return true;
    }
};


wxIMPLEMENT_APP(MyApp);