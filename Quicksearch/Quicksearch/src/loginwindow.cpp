#include "loginwindow.hpp"
#include <iomanip>

void LoginWindow::setTextBoxPlacehol(
    wxTextCtrl* textbox,
    const wxString placeHolder,
    const bool isClosing) {

    textbox -> SetForegroundColour(*wxColour(128, 128, 128));
    textbox -> Bind(wxEVT_SET_FOCUS, [textbox, placeHolder](wxFocusEvent& event) {
        if (textbox ->GetValue() == placeHolder) {
            textbox->SetValue("");
            textbox->SetForegroundColour(*wxBLACK);
        }
        event.Skip();
    });
    textbox -> Bind(wxEVT_KILL_FOCUS, [textbox, placeHolder, isClosing](wxFocusEvent& event) {
        if (!isClosing && textbox -> GetValue().IsEmpty()) {
            textbox->SetValue(placeHolder);
            textbox->SetForegroundColour(*wxColour(128, 128, 128));
        }
        event.Skip();
    });
}

void LoginWindow::setPasswordPlacehol(wxTextCtrl* textbox, const wxString& placeHolder, const bool isClosing) {

    // 1. Initial State: No password masking, grey text
    textbox->SetWindowStyleFlag( wxTE_CENTER); //center text
    textbox->SetForegroundColour(wxColour(128, 128, 128));
    textbox->SetValue(placeHolder);

    // 2. Handle Gaining Focus
    textbox->Bind(wxEVT_SET_FOCUS, [textbox, placeHolder](wxFocusEvent& event) {
        if (textbox->GetValue() == placeHolder) {
            textbox->SetValue("");
            textbox->SetWindowStyleFlag(wxTE_CENTER | wxTE_PASSWORD); 
            textbox->SetForegroundColour(*wxBLACK);
            
            // Refresh the control to apply the style change visually
            textbox->Refresh(); 
        }
        event.Skip();
    });

    // 3. Handle Losing Focus
    textbox->Bind(wxEVT_KILL_FOCUS, [isClosing, textbox, placeHolder](wxFocusEvent& event) {
        if (!isClosing && textbox->GetValue().IsEmpty()) {
            // Disable password masking to show the hint text
            textbox->SetWindowStyleFlag( wxTE_CENTER);
            textbox->SetForegroundColour(wxColour(128, 128, 128));
            textbox->SetValue(placeHolder);

            textbox->Refresh();
        }
        event.Skip();
    });
}

// hashes the password into sha256 and converts the hash into a 64 byte long string 
void LoginWindow::hashPassword(std::string passBuffer) {
     unsigned char hash[crypto_hash_sha256_BYTES];

    // hashes the password in the buffer into sha256 and place it in a temporary sha256 buffer
    crypto_hash_sha256(hash, (const unsigned char *)passBuffer.c_str(), passBuffer.size());

    std::stringstream ss;

    // Converts each bytes of the sha256 hash into an integer and then into it's hex character set to two bytes
    for (int i = 0; i < crypto_hash_sha256_BYTES; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    // after the loop converrsion above it then stores it as a string object
    password = ss.str();
};


void LoginWindow::sendInput(wxCommandEvent& event) {
    firstname = firstnameBox->GetValue().ToStdString();
    lastname = lastnameBox->GetValue().ToStdString();
    hashPassword(passwordBox->GetValue().ToStdString());

    login(firstname, lastname, password);
}


LoginWindow::LoginWindow(const std::string& title)
    : wxFrame(nullptr, wxID_ANY, title,
              wxDefaultPosition, wxSize(400, 400),
              wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX)
{
    this->Center();

      // everything widget goes here

    wxPanel* panel = new wxPanel(this);
    wxPanel* line = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(300, 1));

    wxSize panelFizedSize {300, 400};
    panel -> SetMinSize(panelFizedSize);
    panel -> SetMaxSize(panelFizedSize);

    line->SetBackgroundColour(wxColour(200,200,200));  // light gray line

    panel->SetBackgroundColour( wxColour(*wxWHITE));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // --- Logo image ---
    wxImage::AddHandler(new wxPNGHandler());        // to handle png file
    wxImage img(LOGO, wxBITMAP_TYPE_PNG);    // load png image
    wxStaticBitmap* logo;

    if (img.IsOk()) {
        img = img.Scale(250, 100, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(img);
        mainSizer->AddStretchSpacer(2);
        // show image
        logo = new wxStaticBitmap(panel, wxID_ANY, bitmap);
    }



    // Place holder logic for firstname and lastname box
    // --- Firstname text box ---
    firstnameBox = new wxTextCtrl(
            panel, wxID_ANY, firstnameBoxPlaceHol, wxDefaultPosition, 
            wxSize(200,30),  wxTE_CENTER | wxBORDER_NONE
    ); setTextBoxPlacehol(firstnameBox, firstnameBoxPlaceHol, isClosing);

    // --- Lastname text box ---
    lastnameBox = new wxTextCtrl(
        panel, wxID_ANY, lastnameBoxPlaceHol, wxDefaultPosition, 
        wxSize(200,30),  wxTE_CENTER |  wxBORDER_NONE
    ); setTextBoxPlacehol(lastnameBox, lastnameBoxPlaceHol, isClosing);

    // -- Password text box
    passwordBox = new wxTextCtrl(
        panel, wxID_ANY, passwordBoxPlaceHol, wxDefaultPosition, 
        wxSize(200,30),  wxTE_CENTER | wxBORDER_NONE
    ); setPasswordPlacehol(passwordBox, passwordBoxPlaceHol, isClosing);
    
    
    wxButton*  btnEnter = new wxButton(
    panel, wxID_ANY, "Login  ", wxDefaultPosition,
            wxSize(200,30), wxBORDER_NONE);
    btnEnter->SetBackgroundColour(* wxColour(168, 212, 255));

    // ---- set all widgets into their proper position

    mainSizer-> AddStretchSpacer(5);  // push everything to vertical center
    mainSizer->Add(logo, 0, wxALIGN_CENTER | wxBOTTOM, 15);
    mainSizer->Add(line, 0, wxALIGN_CENTER | wxBOTTOM, 50);
    mainSizer->Add(firstnameBox, 0, wxALIGN_CENTER | wxBOTTOM );
    mainSizer->Add(lastnameBox, 0, wxALIGN_CENTER | wxBOTTOM);
    mainSizer->Add(passwordBox, 0, wxALIGN_CENTER | wxBOTTOM);
    mainSizer-> AddSpacer(30);  // push everything to vertical center
    mainSizer->Add(btnEnter, 0, wxALIGN_RIGHT | wxRIGHT, 100);
    mainSizer-> AddStretchSpacer(4);  // push everything to vertical center
    panel->SetSizer(mainSizer);


    // handle login button upon click
    btnEnter -> Bind(wxEVT_BUTTON, &LoginWindow::sendInput, this);
    // “Only run placeholder logic if we are NOT closing.”
    this->Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent& event)
    {
        isClosing = true;
        event.Skip();
    });    

    // 2. Handle Mouse Hover (Enter)
    btnEnter->Bind(wxEVT_ENTER_WINDOW, [btnEnter](wxMouseEvent& event) {
        btnEnter->SetBackgroundColour(wxColour(0, 105, 217)); // Darker Blue
        btnEnter->Refresh(); // Ensure the OS redraws the button
    event.Skip();
    });

        // 3. Handle Mouse Leave (Exit)
    btnEnter->Bind(wxEVT_LEAVE_WINDOW, [btnEnter](wxMouseEvent& event) {
        btnEnter->SetBackgroundColour(wxColour(168, 212, 255)); // Back to Original
        btnEnter->Refresh();
        event.Skip();
    });
}
