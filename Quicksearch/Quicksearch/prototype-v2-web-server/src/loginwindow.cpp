#include "loginwindow.hpp"
#include <exception>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

#define LOGO "./assets/quicksearch_logo.png"

LoginWindow::LoginWindow(std::shared_ptr<spdlog::logger> FILE_LOG, const std::string& title)
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

    this -> btnEnter -> Bind(wxEVT_BUTTON, [this](wxCommandEvent&event) {
        httplib::Client cli("127.0.0.1", 8080);
        nlohmann::json data;
        data = {
            {"username",  firstnameBox->GetValue().ToStdString()}, 
            {"password", passwordBox->GetValue().ToStdString()}};

        if (auto res = cli.Post("/auth/session", data.dump(), "application/json")) {;
            if(res->status == 200 ) {
                auto data = nlohmann::json::parse(res->body);
                std::string token = data.at("token");
                std::cout << res->status << " " << res->reason << " " << token << std::endl;
            } else {

                auto data = nlohmann::json::parse(res->body);
                std::string log = data.at("error");
                std::cout << res->status << " " << res->reason << " " << log << std::endl;
            }
        }
    });
}

