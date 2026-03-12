#include "adminpanel.hpp"


#define WIDTH 1300
#define HEIGHT 800

AdminPanel::AdminPanel(const wxString& title) : wxFrame (
nullptr,
    wxID_ANY,
    title,
    wxDefaultPosition,
    wxSize(WIDTH, HEIGHT),
    wxDEFAULT_FRAME_STYLE
) {
}