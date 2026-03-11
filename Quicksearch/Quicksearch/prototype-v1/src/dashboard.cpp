#include "dashboard.hpp"


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

    refreshButton -> Bind(wxEVT_BUTTON, [this, user](wxCommandEvent& event){
        loadCustomers(user -> getConnection());
    });
    
    // =========================
    // RESULTS TABLE

    resultList = new wxListCtrl(
        panel,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE 
    );

    resultList->SetFont(dataTableFont);

    // Set all collumn
    resultList->InsertColumn(0,  "Credentials", wxLIST_FORMAT_LEFT, 100);
    resultList->InsertColumn(1,  "Firstname", wxLIST_FORMAT_LEFT, 120);
    resultList->InsertColumn(2,  "Lastname", wxLIST_FORMAT_LEFT, 120);
    resultList->InsertColumn(3,  "Age", wxLIST_FORMAT_LEFT, 50);
    resultList->InsertColumn(4,  "Sex", wxLIST_FORMAT_LEFT, 50);
    resultList->InsertColumn(5,  "Contact", wxLIST_FORMAT_LEFT, 120);
    resultList->InsertColumn(6,  "Occupation", wxLIST_FORMAT_LEFT, 150);
    resultList->InsertColumn(7,  "Date of Birth", wxLIST_FORMAT_LEFT, 110);
    resultList->InsertColumn(8,  "Place of Birth", wxLIST_FORMAT_LEFT, 150);
    resultList->InsertColumn(9,  "Address", wxLIST_FORMAT_LEFT, 250);
    resultList->InsertColumn(10,  "Plan (Mbps)", wxLIST_FORMAT_LEFT, 90);
    resultList->InsertColumn(11, "Date Applied", wxLIST_FORMAT_LEFT, 110);
    resultList->InsertColumn(12, "LP", wxLIST_FORMAT_LEFT, 60);
    resultList->InsertColumn(13, "NP", wxLIST_FORMAT_LEFT, 60);
    resultList->InsertColumn(14, "Port", wxLIST_FORMAT_LEFT, 60);
    resultList->InsertColumn(15, "Optical", wxLIST_FORMAT_LEFT, 70);
    resultList->InsertColumn(16, "SC Connector", wxLIST_FORMAT_LEFT, 110);
    resultList->InsertColumn(17, "FbrDrop", wxLIST_FORMAT_LEFT, 80);
    resultList->InsertColumn(18, "Tapping", wxLIST_FORMAT_LEFT, 80);
    resultList->InsertColumn(19, "Cable Tie", wxLIST_FORMAT_LEFT, 90);
    resultList->InsertColumn(20, "FClamp", wxLIST_FORMAT_LEFT, 80);
    resultList->InsertColumn(21, "Installed By", wxLIST_FORMAT_LEFT, 140);

    resultList->SetBackgroundColour(*wxWHITE);

    mainSizer->Add(resultList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    panel->SetSizer(mainSizer);

    loadCustomers(user -> getConnection());
}


// STUDY THIS
void DataDashboard::loadCustomers(std::shared_ptr<sql::Connection> conn)
{
    try {

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(
                "SELECT firstname, lastname, age, sex, contact, occupation, "
                "date_of_birth, place_of_birth, address, mbps_plan, date_applied, "
                "LP, NP, port, optical, sc_connector, fbrDrop, tapping, cabbleTie, fClamp, installedBy "
                "FROM customers"
            )
        );

        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());

        resultList->DeleteAllItems();

        // next() method always points to a row not column
        while (res->next()) {

            /*
                getitemcount() is the trick to always point at the bottom since an empty list is count 
                as 0 by that function but when you put it in that parametter it is seen as the first row of the table list
            */

            long row = resultList->InsertItem(
                resultList->GetItemCount(),
                wxString(res->getString("firstname"))
            );

            resultList->SetItem(row, 1, wxString(res->getString("lastname")));
            resultList->SetItem(row, 2, wxString::Format("%d", res->getInt("age")));
            resultList->SetItem(row, 3, wxString(res->getString("sex")));
            resultList->SetItem(row, 4, wxString::Format("%lld", res->getInt64("contact")));
            resultList->SetItem(row, 5, wxString(res->getString("occupation")));

            resultList->SetItem(row, 6, wxString(res->getString("date_of_birth")));
            resultList->SetItem(row, 7, wxString(res->getString("place_of_birth")));
            resultList->SetItem(row, 8, wxString(res->getString("address")));

            resultList->SetItem(row, 9, wxString::Format("%d", res->getInt("mbps_plan")));

            resultList->SetItem(row, 10, wxString(res->getString("date_applied")));

            resultList->SetItem(row, 11, wxString::Format("%d", res->getInt("LP")));
            resultList->SetItem(row, 12, wxString::Format("%d", res->getInt("NP")));
            resultList->SetItem(row, 13, wxString::Format("%d", res->getInt("port")));

            resultList->SetItem(row, 14, wxString::Format("%d", res->getInt("optical")));
            resultList->SetItem(row, 15, wxString::Format("%d", res->getInt("sc_connector")));

            resultList->SetItem(row, 16, wxString::Format("%d", res->getInt("fbrDrop")));
            resultList->SetItem(row, 17, wxString::Format("%d", res->getInt("tapping")));
            resultList->SetItem(row, 18, wxString::Format("%d", res->getInt("cabbleTie")));
            resultList->SetItem(row, 19, wxString::Format("%d", res->getInt("fClamp")));

            resultList->SetItem(row, 20, wxString(res->getString("installedBy")));
        }

    }
    catch (sql::SQLException& e) {
        wxMessageBox("Database Error: " + wxString(e.what()), "Error");
    }
}