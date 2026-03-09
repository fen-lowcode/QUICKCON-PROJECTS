#include "loginwindow.hpp"
#include "accountuser.hpp"
#include "wx/sizer.h"
#include "wx/wx.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 400

LoginWindow::LoginWindow(const std::string& title, std::shared_ptr<User> user)
    : wxFrame(nullptr, wxID_ANY, title,
            wxDefaultPosition, wxSize(WINDOW_WIDTH, WINDOW_HEIGHT),
            wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX)
{

    this -> user = user;
    this->Center();

    // every widget goes in this panel 
    wxPanel* panel = new wxPanel(this);
    wxPanel* line = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(600, 1));
    wxSize panelFizedSize {300, 400};

    panel -> SetMinSize(panelFizedSize);
    panel -> SetMaxSize(panelFizedSize);
    panel->SetBackgroundColour(wxColour(245,245,245)); // light modern gray
    line->SetBackgroundColour(wxColour(200,200,200));  // light gray line
    panel->SetBackgroundColour( wxColour(*wxWHITE));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); 
    wxBoxSizer* usernamesizer = new wxBoxSizer(wxHORIZONTAL);

    // --- Logo image ---
    wxImage::AddHandler(new wxPNGHandler());        // to handle png file
    wxImage img(LOGO, wxBITMAP_TYPE_PNG);    // load png image
    wxStaticBitmap* logo;

    // check if logo is loaded properly
    if (img.IsOk()) {
        img = img.Scale(250, 100, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(img);
        mainSizer->AddStretchSpacer(2);
        // show image
        logo = new wxStaticBitmap(panel, wxID_ANY, bitmap);
    }

    // Place holder logic for firstname and lastname box
    // --- Firstname text box ---
    firstnameBox = std::make_unique<wxTextCtrl>(
            panel, wxID_ANY, "", wxDefaultPosition, 
            wxSize(300,30),  wxTE_CENTER 
    ); firstnameBox -> SetHint("Firstname");

      // --- Lastname text box ---
    lastnameBox = std::make_shared<wxTextCtrl>(
        panel, wxID_ANY, "", wxDefaultPosition, 
        wxSize(300,30),  wxTE_CENTER  
    ); lastnameBox -> SetHint("Lastname");

     // -- Password text box
    passwordBox =  std::make_shared<wxTextCtrl>(
        panel, wxID_ANY, "", wxDefaultPosition, 
        wxSize(610,30),  wxTE_CENTER | wxTE_PASSWORD
    ); passwordBox -> SetHint("Password");
    
    btnEnter = std::make_shared<wxButton>(
        panel, wxID_ANY, "Login", wxDefaultPosition,
        wxSize(200,30), wxBORDER_NONE
    ); btnEnter->SetBackgroundColour(*wxWHITE);

    // ---- set all widgets into their proper position
    mainSizer-> AddStretchSpacer(5);  // push everything to vertical center
    mainSizer->Add(logo, 0, wxALIGN_CENTER | wxBOTTOM, 15);
    mainSizer->Add(line, 0, wxALIGN_CENTER | wxBOTTOM, 50);
    usernamesizer->Add(firstnameBox.get(), 0, wxALIGN_CENTER, 50);
    usernamesizer-> AddSpacer(10);
    usernamesizer->Add(lastnameBox.get(), 0, wxALIGN_CENTER, 50);
    mainSizer -> Add(usernamesizer, 0, wxALIGN_CENTER);
    mainSizer-> AddStretchSpacer(1);
    mainSizer->Add(passwordBox.get(), 0, wxALIGN_CENTER | wxBOTTOM);
    mainSizer-> AddSpacer(30);  // push everything to vertical center
    mainSizer->Add(btnEnter.get(), 0, wxALIGN_CENTER);
    mainSizer-> AddStretchSpacer(4);  // push everything to vertical center
    panel->SetSizer(mainSizer);
    this -> btnEvents();

}

// hashes the password into sha256 and converts the hash into a 64 byte long string 
std::string LoginWindow::hashPassword(std::string passBuffer) {
    unsigned char hash[crypto_hash_sha256_BYTES];

    // hashes the password in the buffer into sha256 and place it in a temporary sha256 buffer
    crypto_hash_sha256(hash, (const unsigned char *)passBuffer.c_str(), passBuffer.size());

    std::stringstream ss;

    // Converts each bytes of the sha256 hash into an integer and then into it's hex character set to two bytes
    for (int i = 0; i < crypto_hash_sha256_BYTES; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    // after the loop converrsion above it then stores it as a string object
    return ss.str();
};

void LoginWindow::btnEvents() {

    // handle login button upon click
    btnEnter -> Bind(wxEVT_BUTTON, &LoginWindow::initializeLogin, this);
    // “Only run placeholder logic if we are NOT closing.”
    this->Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent& event)
    {
        isClosing = true;
        event.Skip();
    });    

    // Capture the raw pointer and name it 'btnEnter' inside the lambda
    btnEnter->Bind(wxEVT_ENTER_WINDOW, [btnEnter = btnEnter.get()](wxMouseEvent& event) {
            btnEnter->SetBackgroundColour(wxColour(0, 105, 217)); 
            btnEnter->Refresh(); 
            event.Skip();
        }
    ); // Added the missing };

        // 3. Handle Mouse Leave (Exit)
    btnEnter->Bind(wxEVT_LEAVE_WINDOW, [btnEnter = btnEnter.get()](wxMouseEvent& event) {
            btnEnter->SetBackgroundColour(*wxWHITE); // Back to Original
            btnEnter->Refresh();
            event.Skip();
        }   
    );
}


void LoginWindow::initializeLogin(wxCommandEvent& event) {

    user -> setUsername(
        firstnameBox->GetValue().ToStdString(), 
        lastnameBox->GetValue().ToStdString()
    );

    user -> setPassword(
        hashPassword(passwordBox->GetValue().ToStdString())
    );

    if (user -> login() == true) {
        user ->checkIsAdmin();
        user->identifyCollectors();

        DataDashboard* dashboard = new DataDashboard("Quicksearch Data Management", user);
        dashboard -> Show();

        this -> Destroy();

    }
}