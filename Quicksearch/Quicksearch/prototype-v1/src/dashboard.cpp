#include "dashboard.hpp"
#include "wx/gtk/dataview.h"


DataDashboard::DataDashboard(const wxString& title, std::shared_ptr<User> user)
: wxFrame(
    nullptr,
    wxID_ANY,
    title,
    wxDefaultPosition,
    wxSize(WIDTH, HEIGHT),
    wxDEFAULT_FRAME_STYLE
) {

    wxPanel* panel = new wxPanel(this);

    // panel->SetBackgroundColour(wxColour(245,245,245)); // light modern gray

    // =========================
    // MAIN SIZER

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // =========================
    // HEADER SECTION

    wxBoxSizer* headerSizer = new wxBoxSizer(wxVERTICAL);

    std::string usrname {user->fetchUsername()};
    wxStaticText* welcomeMessage =
        new wxStaticText(panel, wxID_ANY,
            "WELCOME " + wxString(usrname));

    wxFont welcomeMessageFont(15, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_LIGHT);
    wxFont dataTableFont(10, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_LIGHT);

    welcomeMessage ->SetFont(welcomeMessageFont);
    headerSizer->Add(welcomeMessage, 0);
    mainSizer->Add(headerSizer, 0, wxLEFT | wxTOP, 20);


    // SEARCH BAR

    wxFont uiFont(10, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_LIGHT);
    wxBoxSizer* searchSizer {new wxBoxSizer(wxHORIZONTAL)};

    nameSearchBox = new wxSearchCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize); 
    nameSearchBox->SetHint("Search customer info..");  
    nameSearchBox->SetMinSize(wxSize(300,35));
    nameSearchBox->SetFont(uiFont);

    // ------- refresh button experemental
    wxButton*  refreshButton = new wxButton(panel,wxID_ANY, "Refresh table", wxDefaultPosition, wxDefaultSize);
    refreshButton -> SetSize({100, 36});
    refreshButton -> SetFont(uiFont);

    searchSizer  -> Add(nameSearchBox, 0, wxRIGHT, 10);
    searchSizer -> Add(refreshButton, 1 , wxLEFT, 10);
    mainSizer->Add(searchSizer, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 20);

    // refreshButton -> Bind(wxEVT_BUTTON, [this, user](wxCommandEvent& event){
    //     loadCustomers(user -> getConnection());
    // });
    
    // =========================
    // RESULTS TABLE

    customerList = new wxDataViewListCtrl(panel, wxID_ANY);
    customerList->SetFont(dataTableFont);

    customerList->AppendTextColumn("Credentials");
    customerList->AppendTextColumn("Firstname");
    customerList->AppendTextColumn("Lastname");  
    customerList->AppendTextColumn("Age");
    customerList->AppendTextColumn("Sex");
    customerList->AppendTextColumn("Contact");
    customerList->AppendTextColumn("Occupation");
    customerList->AppendTextColumn("Date of Birth");
    customerList->AppendTextColumn("Place of Birth");
    customerList->AppendTextColumn("Address");
    customerList->AppendTextColumn("Plan (MBPS)");
    customerList->AppendTextColumn("Date Applied");
    customerList->AppendTextColumn("LP");
    customerList->AppendTextColumn("NP");
    customerList->AppendTextColumn("Port");
    customerList->AppendTextColumn("Optical");
    customerList->AppendTextColumn("SC Connector");
    customerList->AppendTextColumn("FBR Drop");
    customerList->AppendTextColumn("Tapping");
    customerList->AppendTextColumn("Cable Tie");
    customerList->AppendTextColumn("F Clamp");
    customerList->AppendTextColumn("Installed By");

    customerList->SetBackgroundColour(*wxWHITE);

    
    mainSizer->Add(customerList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    panel->SetSizer(mainSizer);

    // loadCustomers(user -> getConnection());
}

