#include "adminpanel.hpp"
#include "logs.hpp"
#include "user.hpp"
#include "userconfigwindow.hpp"
#include "wx/button.h"
#include "wx/choice.h"
#include "wx/event.h"
#include "wx/gtk/button.h"
#include "wx/layout.h"
#include "wx/variant.h"
#include "wx/wx.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

AdminPanelWindow::AdminPanelWindow(const wxString& title, std::shared_ptr<spdlog::logger> FILE_LOG,  std::shared_ptr<User> user) :  wxFrame (
    nullptr,
    wxID_ANY,
    title,
    wxDefaultPosition, wxSize(WINDOW_WIDTH, WINDOW_HEIGHT), 
    wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX),

    user{user},
    FILE_LOG{FILE_LOG}
{
    this -> SetFont(wxFont(10, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
    wxPanel* panel = new wxPanel(this);
    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    panel -> SetBackgroundColour(wxColour(255, 255, 255)); 

    this -> userTable = new wxDataViewListCtrl(panel, wxID_ANY);
    this -> userTable -> AppendTextColumn("ID");
    this -> userTable -> AppendTextColumn("Firstname");
    this -> userTable -> AppendTextColumn("Lastname");
    this -> userTable -> AppendTextColumn("Admin");
    this -> userTable -> AppendTextColumn("Last Seen");

    wxButton* refreshBtn = new wxButton(panel, wxID_ANY, "Refresh List");
    wxButton* addUserBtn = new wxButton(panel, wxID_ANY, "Add User");

    buttonSizer->Add(refreshBtn, 0, wxALL, 10);
    buttonSizer->Add(addUserBtn, 0, wxALL, 10);
    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT, 20);
    mainSizer->Add(userTable, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    panel->SetSizer(mainSizer);


    this -> showUserMasterlist();

    // to refresh the list
    refreshBtn -> Bind(wxEVT_BUTTON, [this](wxCommandEvent& e){
        this -> showUserMasterlist();
    });

    addUserBtn -> Bind(wxEVT_BUTTON, &AdminPanelWindow::addNewUser, this);

    // triggers to open user configuration window of the selected user in the list
    userTable -> Bind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &AdminPanelWindow::onUserClick, this);
}

void AdminPanelWindow::addNewUser(wxCommandEvent& event) {
    (new UserConfigWindow("Add New User", nullptr, 0, "", "", "")) -> Show();
}

void AdminPanelWindow::showUserMasterlist() {

    auto stmt = std::unique_ptr<sql::PreparedStatement>(
        user->getConnection() -> prepareStatement("SELECT USERID, FIRSTNAME, LASTNAME, ISADMIN, LASTSEEN FROM USERS"));

    try {
        auto res = stmt -> executeQuery();
        userTable ->DeleteAllItems();

        while(res->next()) {
            wxVector<wxVariant> row;
            row.push_back(wxVariant(std::string(res -> getString("USERID"))));
            row.push_back(wxVariant(std::string(res -> getString("FIRSTNAME"))));
            row.push_back(wxVariant(std::string(res -> getString("LASTNAME"))));
            row.push_back(wxVariant(res -> getBoolean("ISADMIN") == true ? "Yes" : "No"));
            row.push_back(wxVariant(std::string(res -> getString("LASTSEEN"))));
            userTable->AppendItem(row);
        }

    } catch(sql::SQLException& e) {
        std::cout << "SQL error" << e.what() << std::endl;
    }
}


//!! IMPROVE THIS
//? EVENT HANDLER THAT PASSES ALL DATA PER COLUMN OF THE SELECTED ROW TO THE CONFIG WINDOW

void AdminPanelWindow::onUserClick(wxDataViewEvent &event) {
    unsigned int col = event.GetColumn();
    wxDataViewItem item = event.GetItem();
    
    // Get the ID from the first column (index 0) of that same row
    wxVariant userId;
    userTable->GetValue(userId, userTable->ItemToRow(item), 0);

    wxVariant userFirstname;
    userTable->GetValue(userFirstname, userTable->ItemToRow(item), 1);

    wxVariant userLastname;
    userTable->GetValue(userLastname, userTable->ItemToRow(item), 2);

    wxVariant userAdminStatus;
    userTable->GetValue(userAdminStatus, userTable->ItemToRow(item), 3);

    std::stringstream logmessage;
    logmessage << "User " << userId.GetInteger() << " is selected";
    LOGDEBUG(FILE_LOG, logmessage.str());


    (
        new UserConfigWindow(
            "Configure User",
            this -> user, 
            userId.GetInteger(), 
            userFirstname.GetString(), 
            userLastname.GetString(), 
            userAdminStatus.GetString()
        )

    )->Show();
}