#pragma once

#include "user.hpp"
#include "logs.hpp"
#include "wx/event.h"
#include "wx/gtk/frame.h"
#include <memory>
#include <spdlog/logger.h>
#include <wx/listctrl.h>
#include <wx/wx.h>
#include <mariadb/conncpp.hpp>
#include <wx/dataview.h>
#include "userconfigwindow.hpp"

class AdminPanelWindow : public wxFrame {
public: 
    AdminPanelWindow( const wxString& title, std::shared_ptr<spdlog::logger> FILE_LOG, std::shared_ptr<User> user);

private:
    std::shared_ptr<spdlog::logger> FILE_LOG;
    std::shared_ptr<User> user;
    wxDataViewListCtrl* userTable {nullptr};

    //!! Temporary var for debugging to get user adminstatus
    bool isAdmin;

    void showUserMasterlist();

    void addNewUser(wxCommandEvent &event);
    void onUserClick(wxDataViewEvent &event);
};
