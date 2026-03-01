#include <nana/gui.hpp>
#include <nana/gui/detail/general_events.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <string>
#include <vector>
#include <iostream>

// ------------------- Authentication -------------------
bool authenticate(const std::string_view firstname, std::string_view lastname, const std::string_view pass, nana::label &message)
{
    if (firstname != "john" || lastname != "smith") {
        message.caption("User does not exist");
        message.fgcolor(nana::colors::red);
        return false;
    } 
    
    if (pass != "1234") {
        message.caption("Login Failed! Check your credentials.");
        message.fgcolor(nana::colors::red);
        return false;
    } 

    return true;
}

// ------------------- Employee Struct -------------------
struct Employee {
    std::string id, name, department, position, email;
};

// ------------------- Employee Table Window -------------------
void show_employee_table()
{
    nana::form fm(nana::API::make_center(1200, 800));
    fm.caption("Employee Directory");

    nana::listbox employee_table{fm, nana::rectangle(400, 10, 800, 790)};
    employee_table.show_header(true);
    employee_table.enable_single(true, false);

    employee_table.append_header("ID", 50);
    employee_table.append_header("Name", 200);
    employee_table.append_header("Department", 150);
    employee_table.append_header("Position", 150);
    employee_table.append_header("Email", 230);

    std::vector<Employee> employees = {
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
        {"021", "Uma Patel", "Design", "UX Designer", "uma@company.com"},
        {"022", "Victor Hugo", "Logistics", "Coordinator", "victor@company.com"},
        {"023", "Wendy Thomas", "Finance", "Treasury Analyst", "wendy@company.com"},
        {"024", "Xavier Lopez", "IT", "Network Engineer", "xavier@company.com"},
        {"025", "Yara Hassan", "Marketing", "SEO Specialist", "yara@company.com"},
        {"026", "Zane Miller", "Sales", "Account Executive", "zane@company.com"},
        {"027", "Abigail Clark", "HR", "Training Specialist", "abigail@company.com"},
        {"028", "Brian Davis", "Finance", "Controller", "brian@company.com"},
        {"029", "Cynthia Hall", "Design", "Creative Director", "cynthia@company.com"},
        {"030", "Derek Evans", "IT", "DevOps Engineer", "derek@company.com"},
        {"031", "Elena Cruz", "Finance", "Payroll Specialist", "elena@company.com"},
        {"032", "Felix Turner", "IT", "Software Engineer", "felix@company.com"},
        {"033", "Georgia Reed", "Marketing", "Brand Manager", "georgia@company.com"},
        {"034", "Harold Knight", "Sales", "Sales Consultant", "harold@company.com"},
        {"035", "Isabella Moore", "HR", "HR Assistant", "isabella@company.com"},
        {"036", "Jason Scott", "Logistics", "Warehouse Manager", "jason@company.com"},
        {"037", "Karen Lopez", "Design", "Graphic Designer", "karen@company.com"},
        {"038", "Liam Turner", "IT", "Backend Developer", "liam@company.com"},
        {"039", "Megan Price", "Finance", "Financial Analyst", "megan@company.com"},
        {"040", "Nathan Brooks", "Sales", "Regional Manager", "nathan@company.com"},
        {"041", "Olivia Sanders", "Marketing", "Social Media Manager", "olivia@company.com"},
        {"042", "Patrick Reed", "IT", "Frontend Developer", "patrick@company.com"},
        {"043", "Queen Alvarez", "HR", "Compensation Analyst", "queen@company.com"},
        {"044", "Ryan Cooper", "Logistics", "Supply Chain Analyst", "ryan@company.com"},
        {"045", "Sophia Bennett", "Design", "Product Designer", "sophia@company.com"},
        {"046", "Thomas Rivera", "Finance", "Budget Analyst", "thomas@company.com"},
        {"047", "Ursula King", "Marketing", "Email Marketing Specialist", "ursula@company.com"},
        {"048", "Victor Stone", "IT", "Cloud Engineer", "victor.stone@company.com"},
        {"049", "Willow Grant", "Sales", "Sales Coordinator", "willow@company.com"},
        {"050", "Xander Young", "HR", "Talent Acquisition Specialist", "xander@company.com"},
        {"051", "Yvonne Carter", "Finance", "Accounts Payable Clerk", "yvonne@company.com"},
        {"052", "Zachary Hill", "IT", "QA Engineer", "zachary@company.com"},
        {"053", "Aiden Flores", "Design", "UI Designer", "aiden@company.com"},
        {"054", "Bella Ward", "Marketing", "Market Research Analyst", "bella@company.com"},
        {"055", "Caleb Morris", "Sales", "Business Development Officer", "caleb@company.com"},
        {"056", "Diana Ross", "HR", "Employee Relations Officer", "diana@company.com"},
        {"057", "Ethan Bailey", "Logistics", "Inventory Specialist", "ethan@company.com"},
        {"058", "Fiona Powell", "Finance", "Tax Specialist", "fiona@company.com"},
        {"059", "Gavin Hughes", "IT", "IT Support Specialist", "gavin@company.com"},
        {"060", "Hannah Simmons", "Marketing", "Content Strategist", "hannah@company.com"}
    };

    employee_table.append("Employees");
    auto cat = employee_table.at(0);
    for (const auto& emp : employees) {
        cat.append({emp.id, emp.name, emp.department, emp.position, emp.email});
    }

    // if a column is selected
    employee_table.events().selected(
    [&](const nana::arg_listbox& arg)
    {
        if (arg.item.selected())
        {
            std::string id = arg.item.text(0);
            std::string name = arg.item.text(1);
            std::string dept = arg.item.text(2);

            std::cout << "Employee Selected:\n";
            std::cout << id << " - " << name << " (" << dept << ")\n";
            
        }
    }
);

    fm.show();
    nana::exec();
}

// ------------------- Login Window -------------------
int main()
{
    nana::form login_win(nana::API::make_center(600, 450));
    login_win.caption("Welcome to QuickSearch");


    nana::textbox firstname(login_win);
    firstname.tip_string("Firstname");
    firstname.move(150, 150);
    firstname.size({200, 25});


    nana::textbox lastname(login_win);
    lastname.tip_string("Lastname");
    lastname.move(150, 180);
    lastname.size({200, 25});

   
    nana::textbox password(login_win);
    password.tip_string("Password");
    password.move(150, 250);
    password.size({200, 25});
    password.multi_lines(false);
    password.mask('*');

    nana::label message(login_win, "");
    message.move(50, 300);
    message.size({300, 25});

    nana::button login_button(login_win, "Login");
    login_button.move(150, 350);
    login_button.size({100, 30});

    login_button.events().click([&] {
        std::string lastname_text = lastname.text();
        std::string firstname_text = firstname.text();
        std::string password_text = password.text();

        if (authenticate(firstname_text, lastname_text, password_text, message)) {
            login_win.close();       // Close login window
            show_employee_table();   // Show employee table
        }
    });

    login_win.show();
    nana::exec();
}
