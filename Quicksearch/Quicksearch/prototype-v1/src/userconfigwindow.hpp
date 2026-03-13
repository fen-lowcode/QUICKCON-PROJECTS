#pragma once
#include "wx/choice.h"
#include "wx/gtk/choice.h"
#include <wx/wx.h>


//TODO: WORK ON THIS

class UserConfigWindow : public wxFrame {

        
private:
    wxPanel* panel;
    wxSizer* userNameTab;

    wxString userID;
    wxString firstname;
    wxString lastname;
    wxString adminStatus;

    wxTextCtrl* userIDTab;
    wxTextCtrl* firstnameTab;
    wxTextCtrl* lastnameTab;
    wxChoice* adminStatusTab;

public:
    UserConfigWindow(const wxString& title, std::string userID, std::string firstname, std::string lastname, std::string adminStatus);
};