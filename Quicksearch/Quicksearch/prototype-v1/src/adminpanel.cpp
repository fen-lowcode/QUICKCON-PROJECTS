#include "adminpanel.hpp"
#include "logs.hpp"
#include "user.hpp"

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

    wxFont uiFont(10, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_LIGHT);
    wxPanel* panel = new wxPanel(this);
    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxSizer* contentSizer = new wxBoxSizer(wxHORIZONTAL);

    userTable = new wxDataViewListCtrl(panel, wxID_ANY);
    userTable -> AppendTextColumn("ID");
    userTable -> AppendTextColumn("Firstname");
    userTable -> AppendTextColumn("Lastname");
    userTable -> AppendTextColumn("Admin");
    userTable -> AppendTextColumn("Last Seen");
    userTable -> SetFont(uiFont);

    mainSizer -> AddSpacer(100);
    mainSizer -> Add(userTable, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);
    panel -> SetSizer(mainSizer);

    // Bind the event to your handler
    userTable->Bind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &AdminPanelWindow::onUserClick, this);
    this -> showUserMasterlist();
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
            row.push_back(wxVariant(std::string(res -> getInt("ISADMIN") == 1 ? "Yes" : "No")));
            row.push_back(wxVariant(std::string(res -> getString("LASTSEEN"))));
            userTable->AppendItem(row);
        }

    } catch(sql::SQLException& e) {
        std::cout << "SQL error" << e.what() << std::endl;
    }
}


//!! IMPROVE THIS
//? EVENT HANDLER THAT SHOWS USERID OF THE SELECTED COLUMN
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

    UserConfigWindow* field = new UserConfigWindow("Configure User",  
        std::string(userId.GetString()),
        std::string(userFirstname.GetString()),
        std::string(userLastname.GetString()), 
        std::string(userAdminStatus.GetString())
    );


    field -> Show();
}