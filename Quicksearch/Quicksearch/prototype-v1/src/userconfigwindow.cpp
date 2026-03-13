#include "userconfigwindow.hpp"
#include "wx/arrstr.h"
#include "wx/choice.h"
#include "wx/event.h"
#include "wx/gdicmn.h"
#include "wx/generic/panelg.h"
#include "wx/gtk/font.h"
#include "wx/gtk/textctrl.h"
#include "wx/layout.h"
#include "wx/panel.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"
#include "wx/wx.h"

//!! WORK ON THIS

UserConfigWindow::UserConfigWindow (const wxString& title, std::string userID, std::string firstname, std::string lastname, std::string adminStatus) :  wxFrame (
    nullptr,
    wxID_ANY,
    title,
    wxDefaultPosition, wxSize(400, 400), 
    wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX),
    userID(userID), firstname(firstname), lastname(lastname), adminStatus(adminStatus)
{
    this->Center();
    this -> SetFont(wxFont(10, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_LIGHT));
    panel = new wxPanel(this);

    // 1. The Main Sizer adds padding around the edges of the window
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // 2. The Grid Sizer: 2 columns, vertical gap of 10px, horizontal gap of 10px
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 10, 20);

    // Make the second column (the text boxes) growable
    gridSizer->AddGrowableCol(1);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, "User ID:"), 0, wxALIGN_CENTER_VERTICAL);
    this->userIDTab = new wxTextCtrl(panel, wxID_ANY, this->userID, wxDefaultPosition, wxDefaultSize, 
        wxTE_READONLY | wxBORDER_NONE);

    gridSizer->Add(this->userIDTab, 0, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, "First Name:"), 0, wxALIGN_CENTER_VERTICAL);
    this->firstnameTab = new wxTextCtrl(panel, wxID_ANY, this->firstname,wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    gridSizer->Add(this->firstnameTab, 0, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, "Last Name:"), 0, wxALIGN_CENTER_VERTICAL);
    this->lastnameTab = new wxTextCtrl(panel, wxID_ANY, this->lastname, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    gridSizer->Add(this->lastnameTab, 0, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, "Admin Status:"), 0, wxALIGN_CENTER_VERTICAL);
    wxArrayString choices;
    choices.Add("Yes");
    choices.Add("No");
    this -> adminStatusTab = new wxChoice(panel,wxID_ANY, wxDefaultPosition, wxDefaultSize, choices, wxBORDER_NONE);
    this -> adminStatusTab -> SetSelection(1);
    gridSizer -> Add(this->adminStatusTab, 0, wxEXPAND);

    // 4. Wrap the grid in the main sizer with a 20px margin for a "breathing" look
    mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 20);
    panel->SetSizer(mainSizer);
}
