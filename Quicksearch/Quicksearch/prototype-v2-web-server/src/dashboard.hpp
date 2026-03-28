#pragma once

#include <iostream>
#include <memory>
#include <wx/wx.h>
#include <wx/dataview.h>
#include <wx/srchctrl.h>
#include "user.hpp"
#include "adminpanel.hpp"



#define WIDTH 1300
#define HEIGHT 800

class DataDashboard : public wxFrame {
public:
    DataDashboard(const wxString& title, std::shared_ptr<User> user);

private:
    std::shared_ptr<User> user;
    wxPanel* panel {nullptr};
};