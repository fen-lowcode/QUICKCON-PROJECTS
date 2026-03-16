#pragma once
#include "wx/choice.h"
#include "wx/gtk/choice.h"
#include <memory>
#include <wx/wx.h>
#include "user.hpp"
#include "wx/gtk/textctrl.h"



class UserConfigWindow : public wxFrame {

        
private:
    std::shared_ptr<User> user;

    wxPanel* panel               {nullptr};

    int userID;
    wxString firstname;
    wxString lastname;
    wxString adminStatus;

    wxTextCtrl* userIDTab       {nullptr};
    wxTextCtrl* firstnameTab     {nullptr};
    wxTextCtrl* lastnameTab     {nullptr};
    wxTextCtrl* changepassTab   {nullptr};
    wxChoice* adminStatusTab    {nullptr};

public:
    UserConfigWindow(const wxString& title, std::shared_ptr<User> user, int userID, wxString  firstname,wxString lastname,wxString adminStatus);
};