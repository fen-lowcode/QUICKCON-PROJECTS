#include "dashboard.hpp"
#include "wx/string.h"


DataDashboard::DataDashboard(const wxString& title, std::shared_ptr<User> user)
: wxFrame(
    nullptr,
    wxID_ANY,
    title,
    wxDefaultPosition,
    wxSize(WIDTH, HEIGHT),
    wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX
) {
    wxPanel* panel = new wxPanel(this);

    // MAIN VERTICAL LAYOUT
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // =====================
    // HEADER (icon + name)
    // =====================
    wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);

    std::string usrname = user -> fetchUsername();
    wxStaticText* usernameLabel = new wxStaticText(panel, wxID_ANY, wxString(usrname));

    headerSizer->Add(usernameLabel, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(headerSizer, 0, wxALL, 10);

    // =====================
    // SEARCH BAR
    // =====================
    searchBox = new wxSearchCtrl(panel, wxID_ANY,"");
    searchBox->SetMinSize(wxSize(200,30));

    mainSizer->Add(searchBox, 0, wxLEFT | wxRIGHT | wxBOTTOM, 10);

    // =====================
    // RESULTS PANEL
    // =====================
    resultList = new wxListCtrl(
        panel,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxLC_REPORT | wxLC_SINGLE_SEL
    );

    resultList->InsertColumn(0, "Firstname", wxLIST_FORMAT_LEFT, 100);
    resultList->InsertColumn(1, "Lastname", wxLIST_FORMAT_LEFT, 100);
    resultList->InsertColumn(2, "Plan", wxLIST_FORMAT_LEFT, 75);
    resultList->InsertColumn(3, "LP", wxLIST_FORMAT_LEFT, 75);
    resultList->InsertColumn(4, "NP", wxLIST_FORMAT_LEFT, 75);
    resultList->InsertColumn(5, "Port", wxLIST_FORMAT_LEFT, 75);
    resultList->InsertColumn(6, "Address", wxLIST_FORMAT_LEFT, 400);

    mainSizer->Add(resultList, 1, wxEXPAND | wxALL, 10);

    panel->SetSizer(mainSizer);

}