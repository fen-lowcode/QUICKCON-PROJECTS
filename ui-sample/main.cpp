
#include <wx/wx.h>
#include <wx/dcbuffer.h>    // for wxAutoBufferedPaintDC
#include <wx/graphics.h>    // for wxGraphicsContext
// Glass panel with light theme
class GlassPanel : public wxPanel {
public:
    GlassPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(360, 260)) {
        SetBackgroundStyle(wxBG_STYLE_PAINT);
        Bind(wxEVT_PAINT, &GlassPanel::OnPaint, this);
    }

private:
    void OnPaint(wxPaintEvent&) {
        wxAutoBufferedPaintDC dc(this);
        dc.Clear();

        wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
        if (gc) {
            wxBrush brush(wxColour(255, 255, 255, 220)); // semi-transparent white
            gc->SetBrush(brush);
            gc->SetPen(*wxTRANSPARENT_PEN);
            gc->DrawRoundedRectangle(0, 0, GetSize().GetWidth(), GetSize().GetHeight(), 16);
            delete gc;
        }
    }
};

class LoginFrame : public wxFrame {
public:
    LoginFrame() : wxFrame(nullptr, wxID_ANY, "QuickSearch", wxDefaultPosition, wxSize(480, 360),
                           wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER|wxMAXIMIZE_BOX))
    {
        SetBackgroundColour(wxColour(240, 240, 245)); // light background

        GlassPanel* glass = new GlassPanel(this);

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* title = new wxStaticText(glass, wxID_ANY, "QuickSearch Login");
        title->SetForegroundColour(wxColour(50, 50, 50));
        title->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        wxTextCtrl* user = new wxTextCtrl(glass, wxID_ANY, "", wxDefaultPosition, wxSize(280,36));
        user->SetHint("Username");
        user->SetBackgroundColour(wxColour(245, 245, 245));
        user->SetForegroundColour(wxColour(30, 30, 30));

        wxTextCtrl* pass = new wxTextCtrl(glass, wxID_ANY, "", wxDefaultPosition, wxSize(280,36), wxTE_PASSWORD);
        pass->SetHint("Password");
        pass->SetBackgroundColour(wxColour(245, 245, 245));
        pass->SetForegroundColour(wxColour(30, 30, 30));

        wxButton* loginBtn = new wxButton(glass, wxID_ANY, "Login", wxDefaultPosition, wxSize(280,40));
        loginBtn->SetBackgroundColour(wxColour(0, 120, 215)); // accent blue
        loginBtn->SetForegroundColour(*wxWHITE);
        loginBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        sizer->AddStretchSpacer();
        sizer->Add(title, 0, wxALIGN_CENTER | wxBOTTOM, 20);
        sizer->Add(user, 0, wxALIGN_CENTER | wxBOTTOM, 12);
        sizer->Add(pass, 0, wxALIGN_CENTER | wxBOTTOM, 20);
        sizer->Add(loginBtn, 0, wxALIGN_CENTER);
        sizer->AddStretchSpacer();

        glass->SetSizer(sizer);

        wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
        frameSizer->AddStretchSpacer();
        frameSizer->Add(glass, 0, wxALIGN_CENTER | wxALL, 20);
        frameSizer->AddStretchSpacer();

        SetSizer(frameSizer);
        Centre();
    }
};

class MyApp : public wxApp {
public:
    bool OnInit() {
        LoginFrame* frame = new LoginFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
