#include <wx/wx.h>

class LoginFrame : public wxFrame {
public:
    LoginFrame() : wxFrame(nullptr, wxID_ANY, "Employee Login", wxDefaultPosition, wxSize(500, 350)) {

        wxPanel* panel = new wxPanel(this);

        wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

        wxStaticText* title = new wxStaticText(panel, wxID_ANY, "Quicksearch Login");
        title->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        wxStaticText* userLabel = new wxStaticText(panel, wxID_ANY, "Full name:");
        usernameCtrl = new wxTextCtrl(panel, wxID_ANY);

        wxStaticText* passLabel = new wxStaticText(panel, wxID_ANY, "Password:");
        passwordCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

        wxButton* loginBtn = new wxButton(panel, wxID_ANY, "Login");

        statusText = new wxStaticText(panel, wxID_ANY, "");

        vbox->Add(title, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
        vbox->Add(userLabel, 0, wxLEFT | wxTOP, 10);
        vbox->Add(usernameCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
        vbox->Add(passLabel, 0, wxLEFT | wxTOP, 10);
        vbox->Add(passwordCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
        vbox->Add(loginBtn, 0, wxALIGN_CENTER | wxTOP, 15);
        vbox->Add(statusText, 0, wxALIGN_CENTER | wxTOP, 5);

        panel->SetSizer(vbox);

        loginBtn->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);
    }

private:
    wxTextCtrl* usernameCtrl;
    wxTextCtrl* passwordCtrl;
    wxStaticText* statusText;

    void OnLogin(wxCommandEvent& event) {
        wxString username = usernameCtrl->GetValue();
        wxString password = passwordCtrl->GetValue();

        // TEMP authentication (replace with MariaDB query later)
        if (username == "Dan" && password == "1234") {
            statusText->SetLabel("Login successful!");
        } else {
            statusText->SetLabel("Invalid credentials");
        }
    }
};

class MyApp : public wxApp {
public:
    bool OnInit() override {
        LoginFrame* frame = new LoginFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
