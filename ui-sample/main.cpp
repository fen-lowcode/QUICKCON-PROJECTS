#include <wx/wx.h>

class LoginFrame : public wxFrame
{
public:
    LoginFrame()
    : wxFrame(nullptr, wxID_ANY, "Welcome to QuickSearch", wxDefaultPosition, wxSize(400, 350))
    {
        wxPanel* panel = new wxPanel(this, wxID_ANY);

        wxStaticText* firstnameLabel = new wxStaticText(panel, wxID_ANY, "Firstname:", wxPoint(50,50), wxDefaultSize);
        firstnameCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150,50), wxSize(200,25));

        wxStaticText* lastnameLabel = new wxStaticText(panel, wxID_ANY, "Lastname:", wxPoint(50,100), wxDefaultSize);
        lastnameCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150,100), wxSize(200,25));

        wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, "Password:", wxPoint(50,150), wxDefaultSize);
        passwordCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150,150), wxSize(200,25), wxTE_PASSWORD);

        messageLabel = new wxStaticText(panel, wxID_ANY, "", wxPoint(50,200), wxSize(300,25));

        wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login", wxPoint(150,250), wxSize(100,30));
        loginButton->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);
    }

private:
    wxTextCtrl* firstnameCtrl;
    wxTextCtrl* lastnameCtrl;
    wxTextCtrl* passwordCtrl;
    wxStaticText* messageLabel;

    void OnLogin(wxCommandEvent& event)
    {
        wxString f = firstnameCtrl->GetValue();
        wxString l = lastnameCtrl->GetValue();
        wxString p = passwordCtrl->GetValue();

        if (f != "john" || l != "smith") {
            messageLabel->SetLabel("User does not exist");
            messageLabel->SetForegroundColour(wxRED);
            return;
        }

        if (p != "1234") {
            messageLabel->SetLabel("Login Failed! Check your credentials.");
            messageLabel->SetForegroundColour(wxRED);
            return;
        }

        Close(); // successful login, close window
    }
};

// App class
class MyApp : public wxApp
{
public:
    virtual bool OnInit() {
        LoginFrame* frame = new LoginFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
