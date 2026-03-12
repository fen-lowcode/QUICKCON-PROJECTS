#include "user.hpp"
#include "wx/string.h"
#include <memory>
#include <wx/listctrl.h>
#include <wx/wx.h>
#include <mariadb/conncpp.hpp>
#include <wx/dataview.h>

class AdminPanel : public wxFrame {
public: 
    AdminPanel(const wxString& title, std::shared_ptr<User> user);

private:
    std::shared_ptr<User> user;
    // wxListCtrl* userTable;
    wxDataViewListCtrl* userTable;
    void showUserMasterlist();
};