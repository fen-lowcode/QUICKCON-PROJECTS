#pragma once
#include "includes.hpp"

class LoginWindow : public wxFrame {
public:
    LoginWindow(const std::string& title);

private:
    wxTextCtrl* firstnameBox;
    wxTextCtrl* lastnameBox;

    wxString firstnameBoxPlaceHol {"                    Firstname"};
    wxString lastnameBoxPlaceHol {"                    Lastname"};
    bool isClosing {false};

    void CheckUsername(wxCommandEvent& event);
};

void LoginWindow::CheckUsername(wxCommandEvent& event) {
    std::string firstname = firstnameBox->GetValue().ToStdString();
    std::string lastname = lastnameBox->GetValue().ToStdString();

    std::cout << firstname << " " << lastname << "\n";
}


LoginWindow::LoginWindow(const std::string& title)
    : wxFrame(nullptr, wxID_ANY, title,
              wxDefaultPosition, wxSize(400, 400),
              wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX)
{
    this->Center();

      // everything widget goes here
    wxPanel* panel = new wxPanel(this);
    wxPanel* line = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(200, 1));

    line->SetBackgroundColour(wxColour(200,200,200));  // light gray line

    panel->SetBackgroundColour(*wxWHITE);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // --- Logo image ---
    wxImage::AddHandler(new wxPNGHandler());        // to handle png file
    wxImage img("assets/quick_search_logo.png", wxBITMAP_TYPE_PNG);    // load png image
    wxStaticBitmap* logo;

    if (img.IsOk()) {
        img = img.Scale(300, 100, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(img);
        mainSizer->AddStretchSpacer(2);
        // show image
        logo = new wxStaticBitmap(panel, wxID_ANY, bitmap);
    }


    // Place holder logic for firstname and lastname box
    // --- Firstname text box ---
    firstnameBox = new wxTextCtrl(
            panel, wxID_ANY, firstnameBoxPlaceHol, wxDefaultPosition, wxSize(200,20)
    );
    
    firstnameBox->SetForegroundColour(*wxLIGHT_GREY);
    firstnameBox->Bind(wxEVT_SET_FOCUS, [this](wxFocusEvent& event) {
        if (firstnameBox->GetValue() == firstnameBoxPlaceHol) {
            firstnameBox->SetValue("");
            firstnameBox->SetForegroundColour(*wxBLACK);
        }
        event.Skip();
    });
    firstnameBox->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event) {
        if (!isClosing && firstnameBox->GetValue().IsEmpty()) {
            firstnameBox->SetValue(firstnameBoxPlaceHol);
            firstnameBox->SetForegroundColour(*wxLIGHT_GREY);
        }
        event.Skip();
    });

    // // --- Lastname text box ---
    lastnameBox = new wxTextCtrl(
        panel, wxID_ANY, lastnameBoxPlaceHol, wxDefaultPosition, wxSize(200,20)
    );

    lastnameBox->SetForegroundColour(*wxLIGHT_GREY);
    lastnameBox->Bind(wxEVT_SET_FOCUS, [this](wxFocusEvent& event) {
        if (lastnameBox->GetValue() == lastnameBoxPlaceHol) {
            lastnameBox->SetValue("");
            lastnameBox->SetForegroundColour(*wxBLACK);
        }
        event.Skip();
    });

    lastnameBox->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event) {
        if (!isClosing && lastnameBox->GetValue().IsEmpty()) {
            lastnameBox->SetValue(lastnameBoxPlaceHol);
            lastnameBox->SetForegroundColour(*wxLIGHT_GREY);
        }
        event.Skip();
    });

    wxButton*  btnEnter = new wxButton(panel, wxID_ANY, "Log in", wxDefaultPosition, wxDefaultSize,  wxBORDER_NONE);


    // ---- set all widgets into their proper position

    mainSizer-> AddStretchSpacer(5);  // push everything to vertical center
    mainSizer->Add(logo, 0, wxALIGN_CENTER | wxBOTTOM, 15);
    mainSizer-> AddStretchSpacer(5);  // push everything to vertical center

    mainSizer->Add(line, 0, wxALIGN_CENTER | wxBOTTOM, 50);
    mainSizer->Add(firstnameBox, 0, wxALIGN_CENTER | wxBOTTOM );
    mainSizer -> AddSpacer(2);
    mainSizer->Add(lastnameBox, 0, wxALIGN_CENTER | wxBOTTOM);
    mainSizer-> AddStretchSpacer(2);  // push everything to vertical center
    mainSizer->Add(btnEnter, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer-> AddStretchSpacer(2);  // push everything to vertical center
    panel->SetSizer(mainSizer);


    btnEnter -> Bind(wxEVT_BUTTON, &LoginWindow::CheckUsername, this);

    // “Only run placeholder logic if we are NOT closing.”
    this->Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent& event)
    {
        isClosing = true;
        event.Skip();
    });    
}
