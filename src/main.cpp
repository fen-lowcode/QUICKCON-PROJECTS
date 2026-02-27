#include <wx/wx.h>

class LoginFrame : public wxFrame {
public:
    LoginFrame() : wxFrame(nullptr, wxID_ANY, "Employee System Login",
                           wxDefaultPosition, wxSize(420, 320)) {

        wxPanel* panel = new wxPanel(this);

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* title = new wxStaticText(panel, wxID_ANY, "Employee Login");
        title->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        wxTextCtrl* username = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(260, -1));
        username->SetHint("Username");

        wxTextCtrl* password = new wxTextCtrl(panel, wxID_ANY, "",
                                              wxDefaultPosition, wxSize(260, -1),
                                              wxTE_PASSWORD);
        password->SetHint("Password");

        wxButton* loginBtn = new wxButton(panel, wxID_ANY, "Login");

        mainSizer->AddStretchSpacer();
        mainSizer->Add(title, 0, wxALIGN_CENTER | wxBOTTOM, 20);
        mainSizer->Add(username, 0, wxALIGN_CENTER | wxBOTTOM, 10);
        mainSizer->Add(password, 0, wxALIGN_CENTER | wxBOTTOM, 20);
        mainSizer->Add(loginBtn, 0, wxALIGN_CENTER);
        mainSizer->AddStretchSpacer();

        panel->SetSizer(mainSizer);
        Centre();
    }
};

class MyApp : public wxApp {
public:
    bool OnInit() {
        LoginFrame* frame = new LoginFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
