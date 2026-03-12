#include "adminpanel.hpp"



#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

AdminPanel::AdminPanel(const wxString& title) : wxFrame (
nullptr,
    wxID_ANY,
    title,
    wxDefaultPosition, wxSize(WINDOW_WIDTH, WINDOW_HEIGHT), wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX)
{
    this -> Center();
    
    wxListCtrl* resultList = new wxListCtrl( panel,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE 
    );

    resultList -> InsertColumn(0,  "ID", wxLIST_FORMAT_LEFT, 10);
    resultList -> InsertColumn(1,  "Firstname", wxLIST_FORMAT_LEFT, 100);
    resultList -> InsertColumn(2,  "Lastname", wxLIST_FORMAT_LEFT, 100);
    resultList -> InsertColumn(3,  "Admin", wxLIST_FORMAT_LEFT, 10);
}