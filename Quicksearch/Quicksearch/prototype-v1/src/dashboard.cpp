#include "dashboard.hpp"

DataDashboard::DataDashboard(const wxString& title, std::shared_ptr<User> user)
: wxFrame(
    nullptr,
    wxID_ANY,
    title,

    wxDefaultPosition,
    wxSize(WIDTH, HEIGHT),
    wxDEFAULT_FRAME_STYLE),
    user(user)
{
    this -> Center();
    this -> SetFont(wxFont(10, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));

    this -> panel = new wxPanel(this);
    this -> panel -> SetBackgroundColour(wxColour(240,240,240)); // light modern gray

}
