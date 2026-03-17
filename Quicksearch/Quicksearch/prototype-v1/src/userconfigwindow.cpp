#include "userconfigwindow.hpp"
#include "wx/choice.h"
#include "wx/event.h"
#include "wx/gdicmn.h"
#include "wx/gtk/button.h"
#include "wx/gtk/stattext.h"
#include "wx/gtk/textctrl.h"
#include "wx/msgdlg.h"
#include "wx/wx.h"
#include <cstddef>
#include <string>

//!! WORK ON THIS

UserConfigWindow::UserConfigWindow (const wxString& title, std::shared_ptr<User> user, int userID, wxString firstname, wxString lastname, wxString adminStatus) :  wxFrame (
    nullptr,
    wxID_ANY,
    title,
    wxDefaultPosition, wxSize(400, 400), 
    wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX),
    user(user), userID(userID), firstname(firstname), lastname(lastname), adminStatus(adminStatus)
{
    this->Center();
    this -> SetFont(wxFont(10, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
    this -> panel = new wxPanel(this);

    // 1. The Main Sizer adds padding around the edges of the window
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // 2. The Grid Sizer: 2 columns, vertical gap of 10px, horizontal gap of 10px
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 10, 20);

    // Make the second column (the text boxes) growable
    gridSizer->AddGrowableCol(1);

    this->userIDTab = new wxTextCtrl(panel, wxID_ANY, std::to_string(this->userID), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxBORDER_NONE);
    this->firstnameTab = new wxTextCtrl(panel, wxID_ANY, this->firstname,wxDefaultPosition, wxDefaultSize,wxBORDER_NONE);
    this->lastnameTab = new wxTextCtrl(panel, wxID_ANY, this->lastname, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    this->changepassTab = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD| wxBORDER_NONE);

    wxArrayString choices; choices.Add("Yes"); choices.Add("No");
    this -> adminStatusTab = new wxChoice(panel,wxID_ANY, wxDefaultPosition, wxDefaultSize, choices, wxBORDER_NONE);

    // automatically sets the right default status
    this -> adminStatusTab -> SetSelection(adminStatus == "Yes" ? 0 : 1);

    wxButton * addUser = new wxButton(panel, wxID_ANY, "Add New User", wxDefaultPosition, wxDefaultSize);
    wxButton * saveButton = new wxButton(panel, wxID_ANY, "Save", wxDefaultPosition, wxDefaultSize);

    // set up grid information layout
    gridSizer->Add(new wxStaticText(panel, wxID_ANY, "User ID:"), 0, wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(this->userIDTab, 0, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, "First Name:"), 0, wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(this->firstnameTab, 0, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, "Last Name:"), 0, wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(this->lastnameTab, 0, wxEXPAND);

    gridSizer -> Add(new wxStaticText(panel, wxID_ANY, "Change Password"), 0, wxALIGN_CENTER_VERTICAL);
    gridSizer -> Add(changepassTab, 0, wxEXPAND);

    gridSizer -> Add(new wxStaticText(panel, wxID_ANY, "Admin Status:"), 0, wxALIGN_CENTER_VERTICAL);
    gridSizer -> Add(this->adminStatusTab, 0, wxEXPAND);


    // 4. Wrap the grid in the main sizer with a 20px margin for a "breathing" look
    mainSizer -> AddSpacer(20);
    mainSizer -> Add(saveButton, 0, wxCENTER, 20);
    mainSizer -> AddSpacer(10);
    mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 20);
    mainSizer -> AddStretchSpacer(1);
    panel->SetSizer(mainSizer);
    
    saveButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        if (this->user->updateUserConfiguration(
            this->userID,
            std::string(this->firstnameTab->GetValue()),
            std::string(this->lastnameTab->GetValue()),
            std::string(this -> changepassTab->GetValue()),
            (this->adminStatusTab->GetSelection() == 0 ? true : false)
        )) {
            wxMessageBox("User Configuration updated Successfully");
        } else {
            wxMessageBox("User Configuration update failed");
        }
    });
}
