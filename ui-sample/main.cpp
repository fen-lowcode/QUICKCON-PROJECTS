#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class LoginWindow : public QWidget {
public:
    LoginWindow() {
        setWindowTitle("Employee Login");
        resize(400, 250);

        QVBoxLayout* layout = new QVBoxLayout(this);

        QLabel* title = new QLabel("Quicksearch Login");
        title->setStyleSheet("font-size: 18px; font-weight: bold;");
        title->setAlignment(Qt::AlignCenter);

        QLabel* nameLabel = new QLabel("Full name:");
        usernameEdit = new QLineEdit();

        QLabel* passLabel = new QLabel("Password:");
        passwordEdit = new QLineEdit();
        passwordEdit->setEchoMode(QLineEdit::Password);

        QPushButton* loginBtn = new QPushButton("Login");

        statusLabel = new QLabel("");
        statusLabel->setAlignment(Qt::AlignCenter);

        layout->addWidget(title);
        layout->addWidget(nameLabel);
        layout->addWidget(usernameEdit);
        layout->addWidget(passLabel);
        layout->addWidget(passwordEdit);
        layout->addWidget(loginBtn);
        layout->addWidget(statusLabel);

        connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    }

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QLabel* statusLabel;

    void handleLogin() {
        QString fullname = usernameEdit->text();
        QString password = passwordEdit->text();

        QStringList parts = fullname.split(" ");

        if (parts.size() < 2) {
            statusLabel->setText("Enter first and last name");
            return;
        }

        QString firstname = parts[0];
        QString lastname  = parts[1];

        // TEMP auth (replace with MariaDB query)
        if (firstname == "Dan" && password == "1234") {
            statusLabel->setText("Login successful!");
        } else {
            statusLabel->setText("Invalid credentials");
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LoginWindow window;
    window.show();

    return app.exec();
}
