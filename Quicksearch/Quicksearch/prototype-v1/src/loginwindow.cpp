#include "loginwindow.hpp"
#include "logs.hpp"
#include <cstdio>
#include <sstream>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

#define LOGO "./assets/quicksearch_logo.png"

LoginWindow::LoginWindow(std::shared_ptr<spdlog::logger> FILE_LOG, const std::string& title, std::shared_ptr<User> user)
    : wxFrame(nullptr, wxID_ANY, title,
            wxDefaultPosition, wxSize(WINDOW_WIDTH, WINDOW_HEIGHT),
            wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX)
{
    this -> FILE_LOG = FILE_LOG;
    this -> user = user;
    this->Center();

    // setting up panel,  every widget goes in this panel 
    panel = new wxPanel(this); panel -> SetMinSize({300, 400});
    panel -> SetMaxSize({300, 400}); panel->SetBackgroundColour( wxColour(*wxWHITE));

    mainSizer = new wxBoxSizer(wxVERTICAL); 
    userNameSizer = new wxBoxSizer(wxHORIZONTAL);

    // render logo

    this -> setUpLogo(); // Render QuickSearch Logo
    this -> setUpInputBoxes(); // render input boxes

    // asign position to all elements 
    mainSizer-> AddStretchSpacer(2);  // push everything to vertical center
    mainSizer->Add(logo, 0, wxALIGN_CENTER | wxBOTTOM, 15);
    mainSizer-> AddStretchSpacer(2);  // push everything to vertical center
    userNameSizer->Add(firstnameBox.get(), 0, wxALIGN_CENTER, 50);
    userNameSizer-> AddSpacer(10);
    userNameSizer->Add(lastnameBox.get(), 0, wxALIGN_CENTER, 50);
    mainSizer -> Add(userNameSizer, 0, wxALIGN_CENTER);
    mainSizer-> AddStretchSpacer(1);
    mainSizer->Add(passwordBox.get(), 0, wxALIGN_CENTER | wxBOTTOM);
    mainSizer-> AddSpacer(10);  // push everything to vertical center
    mainSizer->Add(btnEnter.get(), 0, wxALIGN_CENTER);
    mainSizer-> AddStretchSpacer(4);  // push everything to vertical center
    panel->SetSizer(mainSizer);

    this -> btnEvents();
}


void LoginWindow::setUpInputBoxes() {
    wxFont fontstyle(10, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_LIGHT);
    // --- Firstname text box ---
    firstnameBox = std::make_unique<wxTextCtrl>(
            panel, wxID_ANY, "", wxDefaultPosition, 
            wxSize(200,30),  wxTE_CENTER 
    ); firstnameBox -> SetHint("Firstname"); firstnameBox -> SetFont(fontstyle);

      // --- Lastname text box ---
    lastnameBox = std::make_shared<wxTextCtrl>(
        panel, wxID_ANY, "", wxDefaultPosition, 
        wxSize(200,30),  wxTE_CENTER  
    ); lastnameBox -> SetHint("Lastname"); lastnameBox -> SetFont(fontstyle);

     // -- Password text box
    passwordBox =  std::make_shared<wxTextCtrl>(
        panel, wxID_ANY, "", wxDefaultPosition, 
        wxSize(412,30),  wxTE_CENTER | wxTE_PASSWORD
    ); passwordBox -> SetHint("Password"); passwordBox -> SetFont(fontstyle);
    
    btnEnter = std::make_shared<wxButton>(
        panel, wxID_ANY, "LOGIN", wxDefaultPosition,
        wxSize(200,30), wxBORDER_NONE
    ); btnEnter->SetBackgroundColour(*wxWHITE); btnEnter -> SetFont(fontstyle);
}


// loads the image and define it's properpties
void LoginWindow::setUpLogo() {

    LOGINFO(FILE_LOG, "Login: Initializing logo image");
    wxImage::AddHandler(new wxPNGHandler());        // to handle png file
    wxImage logoImg(LOGO, wxBITMAP_TYPE_PNG);    // load png image

    // check if logo is loaded properly
    if (logoImg.IsOk()) {
        LOGINFO(FILE_LOG, "Login: Initialized Logo image");
        logoImg = logoImg.Scale(270, 110, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(logoImg);
        logo = new wxStaticBitmap(panel, wxID_ANY, bitmap);

    } else {
        LOGERROR(FILE_LOG, "Login: Failed to initialize logo");
        exit(-1);
    }
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
            btnEnter->SetBackgroundColour(wxColour(141, 242, 242)); 
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

    LOGDEBUG(FILE_LOG, "LOGIN BUTTON IS CLICKED");

    user -> setUsername(
        firstnameBox->GetValue().ToStdString(), 
        lastnameBox->GetValue().ToStdString()
    );

    user -> setPassword(
        hashPassword(passwordBox->GetValue().ToStdString())
    );

    // Checks user credentials
    if (user -> login() == true) {

        // checks if the user have already an open session
        // must return FALSE to let the user proceed 
        if (!user -> checkActiveStatus(user->getFirstName(), user->getLastName(), user -> getPassword())) {
            
            std::thread t = std::thread(&User::updateActiveStatus, user);
            t.detach();
            
            // spawn dashboard window
            DataDashboard* dashboard = new DataDashboard("Quicksearch Data Management", user);
            dashboard -> Show();

            // spawn admin panel window
            if(user -> checkIsAdmin()) {
                AdminPanel* adminpanel = new AdminPanel("Quicksearch Admin Panel", user);
                adminpanel -> Show();
            }


            this -> Destroy();
        } else  {

            LOGWARNING(FILE_LOG, "Login: Attempted Multiple Session");
            wxMessageBox(
                "This user is already active, or just recently log out if you are the owner of this account just wait for 30 seconds then try in again", 
                "Login failure"
            );
        }
    }
}