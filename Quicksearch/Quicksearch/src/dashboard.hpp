#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/srchctrl.h>
#include "accountuser.hpp"
#include "wx/gtk/srchctrl.h"
#include "wx/string.h"


#define WIDTH 1300
#define HEIGHT 800

class DataDashboard : public wxFrame {
public:
    DataDashboard(const wxString& title, std::shared_ptr<User> user);

private:
    wxSearchCtrl* nameSearchBox;
    wxSearchCtrl* contactSearchBar;
    wxListCtrl* resultList;

    void loadCustomers(std::shared_ptr<sql::Connection> conn);
};