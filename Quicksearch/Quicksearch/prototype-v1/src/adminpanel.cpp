#include "adminpanel.hpp"
#include "user.hpp"
#include "wx/dataview.h"
#include "wx/listbase.h"
#include "wx/variant.h"
#include "wx/wx.h"
#include <algorithm>
#include <mariadb/conncpp/PreparedStatement.hpp>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

AdminPanel::AdminPanel(const wxString& title,  std::shared_ptr<User> user) :  wxFrame (
nullptr,
    wxID_ANY,
    title,
    wxDefaultPosition, wxSize(WINDOW_WIDTH, WINDOW_HEIGHT), 
    wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX),
    user{user}
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

    this -> showUserMasterlist();
}

void AdminPanel::showUserMasterlist() {

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
            row.push_back(wxVariant(std::string(res -> getString("ISADMIN") == "1" ? "True" : "False")));
            row.push_back(wxVariant(std::string(res -> getString("LASTSEEN"))));
            userTable->AppendItem(row);
        }

    } catch(sql::SQLException& e) {
        std::cout << "SQL error" << e.what() << std::endl;
    }
}
