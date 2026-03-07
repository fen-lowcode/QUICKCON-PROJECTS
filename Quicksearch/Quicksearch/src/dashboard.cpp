#include "dashboard.hpp"


DataDashboard::DataDashboard(const wxString& title)
: wxFrame(
    nullptr,
    wxID_ANY,
    title,
    wxDefaultPosition,
    wxSize(WIDTH, HEIGHT),
    wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX
) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // --- Create Header Panel ---
    wxPanel* headerPanel = new wxPanel(this);
    headerPanel->SetBackgroundColour(*wxLIGHT_GREY); // Set header color
    
    wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* headerText = new wxStaticText(headerPanel, wxID_ANY, "Title Header");
    
    // Make font bold
    wxFont font = headerText->GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD);
    headerText->SetFont(font);

    headerSizer->Add(headerText, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    headerPanel->SetSizer(headerSizer);

    // --- Add Header to Main Sizer ---
    mainSizer->Add(headerPanel, 0, wxEXPAND);
    
    // --- Add Content Area ---
    wxPanel* contentArea = new wxPanel(this);
    mainSizer->Add(contentArea, 1, wxEXPAND);

    this->SetSizer(mainSizer);
}