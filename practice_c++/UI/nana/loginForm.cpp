#include <nana/gui.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <string>
#include <vector>

int main()
{
    // ------------------- Create main form -------------------
    nana::form fm{800, 600, "Employee Table Example"}; 
    // Width=800, Height=600, Window title

    // ------------------- Create listbox (table) -------------------
    nana::listbox employee_table{fm, nana::rectangle(10, 10, 780, 580)};
    // Position (10,10) and size (780x580)
    // This will take most of the form, leaving a 10px margin

    // Enable multiple lines per row if needed
    employee_table.allow_multiple_select(false); // single selection only

    // ------------------- Add columns -------------------
    employee_table.append_header("ID", 50);        // Column 1: width 50 px
    employee_table.append_header("Name", 200);     // Column 2: width 200 px
    employee_table.append_header("Department", 150); // Column 3: width 150 px
    employee_table.append_header("Position", 150);   // Column 4: width 150 px
    employee_table.append_header("Email", 230);      // Column 5: width 230 px

    // ------------------- Add rows -------------------
    // Example data
    struct Employee {
        std::string id, name, department, position, email;
    };

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
        // Add more rows to test scrolling
        {"011", "Kelly Green", "Marketing", "Coordinator", "kelly@company.com"},
        {"012", "Leo Brown", "Sales", "Sales Rep", "leo@company.com"},
        {"013", "Mona Lisa", "Design", "Designer", "mona@company.com"},
        {"014", "Nina White", "HR", "Recruiter", "nina@company.com"},
        {"015", "Oscar Wilde", "Finance", "Analyst", "oscar@company.com"}
    };

    // Insert each employee into the table
    for(const auto& emp : employees)
    {
        nana::listbox::cat_proxy cat = employee_table.at(0); // default category
        cat.append({emp.id, emp.name, emp.department, emp.position, emp.email});
    }

    // ------------------- Scrollable -------------------
    // Nana automatically adds scrollbars if the content exceeds the visible area
    // No extra code needed, scrollbars will appear when needed

    // ------------------- Show form -------------------
    fm.show();
    nana::exec(); // enter Nana event loop

    return 0;
}