#include <wx/wx.h>
#include <wx/listctrl.h>
#include <string>
#include <vector>

// ===================== AUTH =====================
bool authenticate(const std::string_view firstname,
                  const std::string_view lastname,
                  const std::string_view pass)
{
    if (firstname != "john" || lastname != "smith") {
        wxMessageBox("User does not exist", "Login Error", wxOK | wxICON_ERROR);
        return false;
    }

    if (pass != "1234") {
        wxMessageBox("Login Failed! Check your credentials.", "Login Error", wxOK | wxICON_ERROR);
        return false;
    }

    return true;
}

// ===================== DATA MODEL =====================
struct Employee {
    std::string id, name, department, position, email;
};

// ===================== EMPLOYEE TABLE =====================
class EmployeeTableFrame : public wxFrame {
public:
    EmployeeTableFrame()
        : wxFrame(nullptr, wxID_ANY, "Employee Directory",
                  wxDefaultPosition, wxSize(1200, 800))
    {
        wxPanel* panel = new wxPanel(this);

        // ===== SEARCH CONTROLS =====
        wxStaticText* searchLabel =
            new wxStaticText(panel, wxID_ANY, "Search Name:", wxPoint(20, 20));

        searchCtrl =
            new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 45), wxSize(220, 25));
        searchCtrl->Bind(wxEVT_TEXT, &EmployeeTableFrame::OnFilterChanged, this);

        wxStaticText* deptLabel =
            new wxStaticText(panel, wxID_ANY, "Department:", wxPoint(260, 20));

        deptChoice =
            new wxChoice(panel, wxID_ANY, wxPoint(260, 45), wxSize(200, 25));

        deptChoice->Append("All");
        deptChoice->Append("Finance");
        deptChoice->Append("HR");
        deptChoice->Append("IT");
        deptChoice->Append("Marketing");
        deptChoice->Append("Sales");
        deptChoice->Append("Design");
        deptChoice->Append("Logistics");
        deptChoice->SetSelection(0);

        deptChoice->Bind(wxEVT_CHOICE, &EmployeeTableFrame::OnFilterChanged, this);

        // ===== TABLE =====
        employeeTable =
            new wxListCtrl(panel, wxID_ANY, wxPoint(20, 90), wxSize(1150, 670),
                           wxLC_REPORT | wxLC_SINGLE_SEL);

        employeeTable->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 60);
        employeeTable->InsertColumn(1, "Name", wxLIST_FORMAT_LEFT, 220);
        employeeTable->InsertColumn(2, "Department", wxLIST_FORMAT_LEFT, 150);
        employeeTable->InsertColumn(3, "Position", wxLIST_FORMAT_LEFT, 180);
        employeeTable->InsertColumn(4, "Email", wxLIST_FORMAT_LEFT, 250);

        employeeTable->Bind(wxEVT_LIST_ITEM_SELECTED,
                            &EmployeeTableFrame::OnEmployeeSelected, this);

        LoadEmployees();
        RefreshTable();
    }

private:
    wxListCtrl* employeeTable;
    wxTextCtrl* searchCtrl;
    wxChoice* deptChoice;
    std::vector<Employee> employees;

    // ===== LOAD DATA =====
    void LoadEmployees() {
        employees = {
            {"001", "Alice Johnson", "Finance", "Manager", "alice@company.com"},
            {"002", "Bob Smith", "HR", "Recruiter", "bob@company.com"},
            {"003", "Carol Lee", "IT", "Developer", "carol@company.com"},
            {"004", "David Wong", "IT", "System Admin", "david@company.com"},
            {"005", "Eva Green", "Marketing", "Coordinator", "eva@company.com"},
            {"006", "Frank White", "Sales", "Sales Rep", "frank@company.com"},
            {"007", "Grace Kim", "Design", "Designer", "grace@company.com"},
            {"008", "Henry Ford", "Logistics", "Supervisor", "henry@company.com"},
            {"009", "Ivy Zhao", "Finance", "Analyst", "ivy@company.com"},
            {"010", "Jack Black", "IT", "Developer", "jack@company.com"},
            {"011", "Kelly Green", "Marketing", "Coordinator", "kelly@company.com"},
            {"012", "Leo Brown", "Sales", "Sales Rep", "leo@company.com"},
            {"013", "Mona Lisa", "Design", "Designer", "mona@company.com"},
            {"014", "Nina White", "HR", "Recruiter", "nina@company.com"},
            {"015", "Oscar Wilde", "Finance", "Analyst", "oscar@company.com"},
            {"016", "Paul Adams", "Finance", "Accountant", "paul@company.com"},
            {"017", "Quincy Jones", "IT", "Security Specialist", "quincy@company.com"},
            {"018", "Rachel Green", "HR", "HR Manager", "rachel@company.com"},
            {"019", "Sam Carter", "Sales", "Sales Manager", "sam@company.com"},
            {"020", "Tina Brown", "Marketing", "Content Writer", "tina@company.com"},
            {"061", "Aaron Delgado", "IT", "Support Engineer", "aaron@company.com"},
            {"062", "Bianca Reyes", "Finance", "Accounts Analyst", "bianca@company.com"},
            {"063", "Carlos Mendoza", "Logistics", "Fleet Coordinator", "carlos@company.com"},
            {"064", "Denise Flores", "Marketing", "Digital Marketing Specialist", "denise@company.com"},
            {"065", "Edward Tan", "Sales", "Sales Associate", "edward@company.com"},
            {"066", "Faith Navarro", "HR", "HR Coordinator", "faith@company.com"},
            {"067", "George Lim", "IT", "Database Administrator", "george@company.com"},
            {"068", "Hazel Bautista", "Design", "Illustrator", "hazel@company.com"},
            {"069", "Ian Santos", "Finance", "Credit Analyst", "ian@company.com"},
            {"070", "Jasmine Cruz", "Marketing", "Campaign Manager", "jasmine@company.com"},
            {"071", "Kevin Ong", "IT", "Systems Engineer", "kevin@company.com"},
            {"072", "Lara Gomez", "HR", "Recruitment Officer", "lara@company.com"},
            {"073", "Marco Villanueva", "Sales", "Territory Manager", "marco@company.com"},
            {"074", "Nadine Torres", "Design", "UI/UX Specialist", "nadine@company.com"},
            {"075", "Oliver Sy", "Logistics", "Transport Supervisor", "oliver@company.com"},
            {"076", "Patricia Ramos", "Finance", "Billing Specialist", "patricia@company.com"},
            {"077", "Rafael Aquino", "IT", "Security Analyst", "rafael@company.com"},
            {"078", "Samantha Yu", "Marketing", "Copywriter", "samantha@company.com"},
            {"079", "Tristan Velasco", "Sales", "Account Manager", "tristan@company.com"},
            {"080", "Vanessa Chua", "HR", "HR Generalist", "vanessa@company.com"},
            {"081", "Warren Lim", "IT", "Cloud Support Engineer", "warren@company.com"},
            {"082", "Xenia Robles", "Finance", "Investment Analyst", "xenia@company.com"},
            {"083", "Yuri Nakamura", "Design", "Motion Designer", "yuri@company.com"},
            {"084", "Zara Ahmed", "Marketing", "SEO Manager", "zara@company.com"},
            {"085", "Alfred Castro", "Logistics", "Warehouse Supervisor", "alfred@company.com"},
            {"086", "Bea Salazar", "HR", "Training Officer", "bea@company.com"},
            {"087", "Clyde Herrera", "Sales", "Sales Executive", "clyde@company.com"},
            {"088", "Daphne Tan", "Finance", "Audit Associate", "daphne@company.com"},
            {"089", "Elliot Park", "IT", "Software Tester", "elliot@company.com"},
            {"090", "Frances Lopez", "Design", "Brand Designer", "frances@company.com"},
            {"091", "Gerald Santos", "Logistics", "Supply Planner", "gerald@company.com"},
            {"092", "Hannah Cruz", "Marketing", "Social Media Specialist", "hannah.cruz@company.com"},
            {"093", "Ivan Reyes", "IT", "Network Technician", "ivan@company.com"},
            {"094", "Julia Mendoza", "Finance", "Payroll Analyst", "julia@company.com"},
            {"095", "Kenneth Yu", "Sales", "Business Consultant", "kenneth@company.com"},
            {"096", "Lindsay Tan", "HR", "Employee Engagement Officer", "lindsay@company.com"},
            {"097", "Miguel Fernandez", "IT", "Full Stack Developer", "miguel@company.com"},
            {"098", "Nicole Santos", "Marketing", "Content Manager", "nicole@company.com"},
            {"099", "Owen Cruz", "Logistics", "Procurement Officer", "owen@company.com"},
            {"100", "Paula Lim", "Finance", "Risk Analyst", "paula@company.com"},
            {"101", "Quentin Yap", "IT", "DevOps Specialist", "quentin@company.com"},
            {"102", "Rina Gomez", "Design", "Visual Designer", "rina@company.com"},
            {"103", "Sean Bautista", "Sales", "Sales Consultant", "sean@company.com"},
            {"104", "Theresa Ong", "HR", "HR Supervisor", "theresa@company.com"},
            {"105", "Ulysses Tan", "Finance", "Treasury Officer", "ulysses@company.com"},
            {"106", "Victor Ramos", "IT", "IT Operations Engineer", "victor.ramos@company.com"},
            {"107", "Wendy Lim", "Marketing", "Brand Strategist", "wendy@company.com"},
            {"108", "Xander Cruz", "Logistics", "Logistics Analyst", "xander@company.com"},
            {"109", "Yasmin Reyes", "Design", "Product Illustrator", "yasmin@company.com"},
            {"110", "Zion Velasco", "Sales", "Key Account Manager", "zion@company.com"},
            {"111", "Andre Navarro", "IT", "Embedded Systems Engineer", "andre@company.com"},
            {"112", "Bella Mendoza", "Finance", "Financial Controller", "bella@company.com"},
            {"113", "Chris Tan", "Marketing", "Marketing Analyst", "chris@company.com"},
            {"114", "Derek Cruz", "Logistics", "Operations Coordinator", "derek@company.com"},
            {"115", "Eliza Santos", "HR", "HR Specialist", "eliza@company.com"},
            {"116", "Felix Ong", "IT", "AI Engineer", "felix@company.com"},
            {"117", "Gina Lopez", "Design", "Creative Designer", "gina@company.com"},
            {"118", "Harvey Reyes", "Sales", "Regional Sales Officer", "harvey@company.com"},
            {"119", "Isabel Tan", "Finance", "Compliance Officer", "isabel@company.com"},
            {"120", "Jonas Cruz", "IT", "Technical Support Lead", "jonas@company.com"},
        };
    }

    // ===== FILTER + REFRESH =====
    void RefreshTable() {
        employeeTable->DeleteAllItems();

        wxString searchText = searchCtrl->GetValue().Lower();
        wxString selectedDept = deptChoice->GetStringSelection();

        for (const auto& emp : employees) {
            wxString name = emp.name;
            wxString dept = emp.department;

            bool matchName = name.Lower().Find(searchText) != wxNOT_FOUND;
            bool matchDept = (selectedDept == "All" || dept == selectedDept);

            if (matchName && matchDept) {
                long index =
                    employeeTable->InsertItem(employeeTable->GetItemCount(), emp.id);
                employeeTable->SetItem(index, 1, emp.name);
                employeeTable->SetItem(index, 2, emp.department);
                employeeTable->SetItem(index, 3, emp.position);
                employeeTable->SetItem(index, 4, emp.email);
            }
        }
    }

    void OnFilterChanged(wxCommandEvent&) {
        RefreshTable();
    }

    // ===== DETAILS POPUP =====
    void OnEmployeeSelected(wxListEvent& event) {
        long itemIndex = event.GetIndex();
        if (itemIndex != -1) {
            wxString name = employeeTable->GetItemText(itemIndex, 1);
            ShowEmployeeDetails(name);
        }
    }

    void ShowEmployeeDetails(const wxString& name) {
        wxFrame* detailsFrame =
            new wxFrame(this, wxID_ANY, name + " - Details",
                        wxDefaultPosition, wxSize(400, 300));

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(new wxStaticText(detailsFrame, wxID_ANY, "Name: " + name), 0, wxALL, 10);
        sizer->Add(new wxStaticText(detailsFrame, wxID_ANY, "Other Details Here..."), 0, wxALL, 10);

        detailsFrame->SetSizer(sizer);
        detailsFrame->Show();
    }
};

// ===================== LOGIN =====================
class LoginFrame : public wxFrame {
public:
    LoginFrame()
        : wxFrame(nullptr, wxID_ANY, "QuickSearch Login",
                  wxDefaultPosition, wxSize(600, 450))
    {
        SetBackgroundColour(wxColour(255, 255, 255));

        new wxStaticText(this, wxID_ANY, "Firstname", wxPoint(150, 150));
        firstNameTextCtrl =
            new wxTextCtrl(this, wxID_ANY, "", wxPoint(150, 175), wxSize(200, 25));

        new wxStaticText(this, wxID_ANY, "Lastname", wxPoint(150, 200));
        lastNameTextCtrl =
            new wxTextCtrl(this, wxID_ANY, "", wxPoint(150, 225), wxSize(200, 25));

        new wxStaticText(this, wxID_ANY, "Password", wxPoint(150, 250));
        passwordTextCtrl =
            new wxTextCtrl(this, wxID_ANY, "", wxPoint(150, 275), wxSize(200, 25), wxTE_PASSWORD);

        wxButton* loginButton =
            new wxButton(this, wxID_ANY, "Login", wxPoint(150, 325), wxSize(100, 30));

        loginButton->Bind(wxEVT_BUTTON, &LoginFrame::OnLoginButtonClick, this);
    }

private:
    wxTextCtrl* firstNameTextCtrl;
    wxTextCtrl* lastNameTextCtrl;
    wxTextCtrl* passwordTextCtrl;

    void OnLoginButtonClick(wxCommandEvent&) {
        std::string firstname = firstNameTextCtrl->GetValue().ToStdString();
        std::string lastname = lastNameTextCtrl->GetValue().ToStdString();
        std::string password = passwordTextCtrl->GetValue().ToStdString();

        if (authenticate(firstname, lastname, password)) {
            this->Close();
            EmployeeTableFrame* table = new EmployeeTableFrame();
            table->Show();
        }
    }
};

// ===================== APP =====================
class MyApp : public wxApp {
public:
    bool OnInit() override {
        LoginFrame* loginFrame = new LoginFrame();
        loginFrame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);