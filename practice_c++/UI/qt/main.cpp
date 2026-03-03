#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <vector>
#include <string>
#include <algorithm>

// ===== DATA MODEL =====
struct Employee {
    QString id, name, department, position, email;
};

// ===== AUTH FUNCTION =====
bool authenticate(const QString& firstname, const QString& lastname, const QString& pass) {
    if (firstname != "john" || lastname != "smith") {
        QMessageBox::critical(nullptr, "Login Error", "User does not exist");
        return false;
    }
    if (pass != "1234") {
        QMessageBox::critical(nullptr, "Login Error", "Login Failed! Check credentials.");
        return false;
    }
    return true;
}

// ===== EMPLOYEE TABLE =====
class EmployeeTableWindow : public QMainWindow {
    Q_OBJECT
public:
    EmployeeTableWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        QWidget* central = new QWidget(this);
        QVBoxLayout* mainLayout = new QVBoxLayout(central);

        // Search + Dept filter
        QHBoxLayout* filterLayout = new QHBoxLayout();
        filterLayout->addWidget(new QLabel("Search Name:"));
        searchEdit = new QLineEdit();
        filterLayout->addWidget(searchEdit);

        filterLayout->addWidget(new QLabel("Department:"));
        deptCombo = new QComboBox();
        deptCombo->addItem("All");
        deptCombo->addItems({"Finance","HR","IT","Marketing","Sales","Design","Logistics"});
        filterLayout->addWidget(deptCombo);

        mainLayout->addLayout(filterLayout);

        // Table
        table = new QTableWidget();
        table->setColumnCount(5);
        table->setHorizontalHeaderLabels({"ID","Name","Department","Position","Email"});
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        mainLayout->addWidget(table);

        setCentralWidget(central);
        resize(1200,800);

        LoadEmployees();
        RefreshTable();

        // Connections
        connect(searchEdit, &QLineEdit::textChanged, this, &EmployeeTableWindow::RefreshTable);
        connect(deptCombo, &QComboBox::currentTextChanged, this, &EmployeeTableWindow::RefreshTable);
        connect(table, &QTableWidget::cellDoubleClicked, this, &EmployeeTableWindow::ShowEmployeeDetails);
    }

private:
    QLineEdit* searchEdit;
    QComboBox* deptCombo;
    QTableWidget* table;
    std::vector<Employee> employees;

    void LoadEmployees() {
        employees = {
            {"001","Alice Johnson","Finance","Manager","alice@company.com"},
            {"002","Bob Smith","HR","Recruiter","bob@company.com"},
            {"003","Carol Lee","IT","Developer","carol@company.com"},
            {"004","David Wong","IT","System Admin","david@company.com"},
            {"005","Eva Green","Marketing","Coordinator","eva@company.com"},
            {"006","Frank White","Sales","Sales Rep","frank@company.com"},
            {"007","Grace Kim","Design","Designer","grace@company.com"},
            {"008","Henry Ford","Logistics","Supervisor","henry@company.com"},
            {"009","Ivy Zhao","Finance","Analyst","ivy@company.com"},
            {"010","Jack Black","IT","Developer","jack@company.com"}
            // Add more employees as needed...
        };
    }

    void RefreshTable() {
        table->setRowCount(0);
        QString searchText = searchEdit->text().toLower();
        QString selectedDept = deptCombo->currentText();

        for (const auto& emp : employees) {
            bool matchName = emp.name.toLower().contains(searchText);
            bool matchDept = (selectedDept == "All" || emp.department == selectedDept);

            if (matchName && matchDept) {
                int row = table->rowCount();
                table->insertRow(row);
                table->setItem(row,0,new QTableWidgetItem(emp.id));
                table->setItem(row,1,new QTableWidgetItem(emp.name));
                table->setItem(row,2,new QTableWidgetItem(emp.department));
                table->setItem(row,3,new QTableWidgetItem(emp.position));
                table->setItem(row,4,new QTableWidgetItem(emp.email));
            }
        }
    }

    void ShowEmployeeDetails(int row, int /*column*/) {
        if (row < 0 || row >= table->rowCount()) return;
        QString name = table->item(row,1)->text();
        QMessageBox::information(this, name + " - Details", "Details for " + name);
    }
};

// ===== LOGIN WINDOW =====
class LoginWindow : public QWidget {
    Q_OBJECT
public:
    LoginWindow() {
        setWindowTitle("QuickSearch Login");
        resize(600,450);

        QVBoxLayout* layout = new QVBoxLayout(this);

        QLabel* fLabel = new QLabel("Firstname:");
        firstNameEdit = new QLineEdit();
        layout->addWidget(fLabel);
        layout->addWidget(firstNameEdit);

        QLabel* lLabel = new QLabel("Lastname:");
        lastNameEdit = new QLineEdit();
        layout->addWidget(lLabel);
        layout->addWidget(lastNameEdit);

        QLabel* pLabel = new QLabel("Password:");
        passwordEdit = new QLineEdit();
        passwordEdit->setEchoMode(QLineEdit::Password);
        layout->addWidget(pLabel);
        layout->addWidget(passwordEdit);

        QPushButton* loginBtn = new QPushButton("Login");
        layout->addWidget(loginBtn);

        connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::TryLogin);
    }

private:
    QLineEdit* firstNameEdit;
    QLineEdit* lastNameEdit;
    QLineEdit* passwordEdit;

    void TryLogin() {
        QString fn = firstNameEdit->text();
        QString ln = lastNameEdit->text();
        QString pw = passwordEdit->text();

        if (authenticate(fn,ln,pw)) {
            this->close();
            EmployeeTableWindow* tableWin = new EmployeeTableWindow();
            tableWin->show();
        }
    }
};

// ===== MAIN =====
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LoginWindow login;
    login.show();

    return app.exec();
}