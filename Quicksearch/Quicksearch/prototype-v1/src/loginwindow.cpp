#include "loginwindow.hpp"
#include "logs.hpp"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

#define LOGO "./assets/quicksearch_logo.png"

LoginWindow::LoginWindow(std::shared_ptr<spdlog::logger> FILE_LOG, const std::string& title, std::shared_ptr<User> user)
    : wxFrame(nullptr, wxID_ANY, title,
            wxDefaultPosition, wxSize(WINDOW_WIDTH, WINDOW_HEIGHT),
            wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX), FILE_LOG(FILE_LOG),  user(user)
{
    this->Center();
    this -> SetFont(wxFont(10, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));

    // setting up panel,  every widget goes in this panel 
    panel = new wxPanel(this); panel -> SetMinSize({300, 400});
    panel -> SetMaxSize({300, 400}); panel->SetBackgroundColour( wxColour(*wxWHITE));
    panel -> SetBackgroundColour(wxColour(240,240,240)); // light modern gray

    mainSizer = new wxBoxSizer(wxVERTICAL); 
    userNameSizer = new wxBoxSizer(wxHORIZONTAL);

    this -> setUpLogo(); // Render QuickSearch Logo
    this -> setUpInputBoxes(); // render input boxes
    this -> setupLayout();
    this -> btnEvents();
}


void LoginWindow::setupLayout() {
    mainSizer-> AddStretchSpacer(2);  // push everything to vertical center
    mainSizer->Add(logo, 0, wxALIGN_CENTER | wxBOTTOM, 15);
    mainSizer-> AddStretchSpacer(2);  // push everything to vertical center
    userNameSizer->Add(firstnameBox, 0, wxALIGN_CENTER, 50);
    userNameSizer-> AddSpacer(10);
    userNameSizer->Add(lastnameBox, 0, wxALIGN_CENTER, 50);
    mainSizer -> Add(userNameSizer, 0, wxALIGN_CENTER);
    mainSizer-> AddStretchSpacer(1);
    mainSizer->Add(passwordBox, 0, wxALIGN_CENTER | wxBOTTOM);
    mainSizer-> AddSpacer(30);  // push everything to vertical center
    mainSizer->Add(btnEnter, 0, wxALIGN_CENTER);
    mainSizer-> AddStretchSpacer(1);  // push everything to vertical center
    panel->SetSizer(mainSizer);

}


void LoginWindow::setUpInputBoxes() {
    // --- Firstname text box ---
    firstnameBox = new wxTextCtrl (
            panel, wxID_ANY, "", wxDefaultPosition, 
            wxSize(200,30),  wxTE_CENTER 
    ); firstnameBox -> SetHint("Firstname"); 

      // --- Lastname text box ---
    lastnameBox = new wxTextCtrl (
        panel, wxID_ANY, "", wxDefaultPosition, 
        wxSize(200,30),  wxTE_CENTER  
    ); lastnameBox -> SetHint("Lastname"); 

     // -- Password text box
    passwordBox =  new wxTextCtrl (
        panel, wxID_ANY, "", wxDefaultPosition, 
        wxSize(412,30),  wxTE_CENTER | wxTE_PASSWORD
    ); passwordBox -> SetHint("Password"); 
    
    btnEnter = new wxButton (
        panel, wxID_ANY, "LOGIN", wxDefaultPosition,
        wxSize(200,30), wxBORDER_NONE
    ); btnEnter->SetBackgroundColour(*wxWHITE);
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
    this -> btnEnter->Bind(wxEVT_ENTER_WINDOW, [this](wxMouseEvent& event) {
            this -> btnEnter->SetBackgroundColour(wxColour(141, 242, 242)); 
            this -> btnEnter->Refresh(); 
            event.Skip();
        }
    ); // Added the missing };

        // 3. Handle Mouse Leave (Exit)
    this -> btnEnter->Bind(wxEVT_LEAVE_WINDOW, [this](wxMouseEvent& event) {
            this -> btnEnter->SetBackgroundColour(*wxWHITE); // Back to Original
            this -> btnEnter->Refresh();
            event.Skip();
        }   
    );
}


void LoginWindow::initializeLogin(wxCommandEvent& event) {

    LOGDEBUG(FILE_LOG, "LOGIN BUTTON IS CLICKED");

    this -> user -> setUsername(
        firstnameBox->GetValue().ToStdString(), 
        lastnameBox->GetValue().ToStdString()
    );
    this -> user -> setPassword(passwordBox->GetValue().ToStdString());

    // Checks user credentials
    if (user -> login() == true) {

        // checks if the user have already an open session
        // must return FALSE to let the user proceed 
        LOGDEBUG(FILE_LOG, user -> getPassword());
        if (!this -> user -> checkActiveStatus(user->getFirstName(), user->getLastName())) {
            
            std::thread t = std::thread(&User::updateActiveStatus, user);
            t.detach();

            //!! spawn dashboard window
            (new DataDashboard("Quicksearch Data Management", user)) -> Show();

            // spawn admin panel window
            if(this -> user -> checkIsAdmin()) {
                (new AdminPanelWindow("Quicksearch Admin Panel", FILE_LOG, user)) -> Show();
            }


            this -> Destroy();
    
        } else  {

            LOGWARNING(FILE_LOG, "Login: Attempted Multiple Session");
            wxMessageBox(
                "This user is already active, or just recently log out if you are the owner of this account just wait for 15 seconds then try in again", 
                "Login failure"
            );
        }
    }
}