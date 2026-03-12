#include "wx/string.h"
#include "wx/listctrl.h"
#include <wx/wx.h>

class AdminPanel : public wxFrame {
public: 
    AdminPanel(const wxString& title);

private:
    wxFont uiFont;
    wxPanel* panel;
    wxSizer* mainSizer;
};