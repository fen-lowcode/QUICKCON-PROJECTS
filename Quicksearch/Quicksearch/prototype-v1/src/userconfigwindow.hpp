#pragma once
#include "wx/choice.h"
#include "wx/gtk/choice.h"
#include <memory>
#include <wx/wx.h>
#include "user.hpp"



class UserConfigWindow : public wxFrame {

        
private:
    std::shared_ptr<User> user;
    wxPanel* panel;
    wxSizer* userNameTab;

    int userID;
    wxString firstname;
    wxString lastname;
    wxString adminStatus;

    wxTextCtrl* userIDTab;
    wxTextCtrl* firstnameTab;
    wxTextCtrl* lastnameTab;
    wxChoice* adminStatusTab;

public:
    UserConfigWindow(const wxString& title, std::shared_ptr<User> user, int userID, wxString  firstname,wxString lastname,wxString adminStatus);
};