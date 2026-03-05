#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFont>
#include <QFrame>
#include <QIcon>

class LoginWindow : public QWidget
{
public:
    LoginWindow(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setWindowTitle("QuickSearch Pro Login");
        resize(400, 300);
        setStyleSheet("background-color: #f5f5f5;");

        // Center card frame
        QFrame *card = new QFrame(this);
        card->setFixedSize(320, 240);
        card->setStyleSheet(
            "QFrame {"
            "background-color: #ffffff;"
            "border-radius: 12px;"
            "border: 1px solid #dcdcdc;"
            "}"
        );
        card->move((width() - card->width())/2, (height() - card->height())/2);

        // Layout inside card
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setContentsMargins(24, 24, 24, 24);
        cardLayout->setSpacing(12);

        // Title
        QLabel *title = new QLabel("QuickSearch Pro");
        QFont titleFont("Segoe UI", 20, QFont::Bold);
        title->setFont(titleFont);
        title->setAlignment(Qt::AlignCenter);

        QLabel *subtitle = new QLabel("Enter your credentials");
        QFont subFont("Segoe UI", 10);
        subtitle->setFont(subFont);
        subtitle->setAlignment(Qt::AlignCenter);
        subtitle->setStyleSheet("color: #666666;");

        // Username
        usernameEdit = new QLineEdit;
        usernameEdit->setPlaceholderText("Username");
        usernameEdit->setStyleSheet(
            "QLineEdit {"
            "border: 1px solid #cccccc;"
            "border-radius: 6px;"
            "padding: 6px 8px;"
            "background-color: #f9f9f9;"
            "color: #333333;"
            "}"
            "QLineEdit:focus {"
            "border: 1px solid #1a73e8;"
            "background-color: #ffffff;"
            "}"
        );

        // Password
        passwordEdit = new QLineEdit;
        passwordEdit->setPlaceholderText("Password");
        passwordEdit->setEchoMode(QLineEdit::Password);
        passwordEdit->setStyleSheet(
            "QLineEdit {"
            "border: 1px solid #cccccc;"
            "border-radius: 6px;"
            "padding: 6px 8px;"
            "background-color: #f9f9f9;"
            "color: #333333;"
            "}"
            "QLineEdit:focus {"
            "border: 1px solid #1a73e8;"
            "background-color: #ffffff;"
            "}"
        );

        // Login Button
        QPushButton *loginButton = new QPushButton("Login");
        loginButton->setFixedHeight(36);
        loginButton->setStyleSheet(
            "QPushButton {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #1a73e8, stop:1 #4285f4);"
            "border-radius: 8px;"
            "color: white;"
            "font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #1669c1, stop:1 #357ae8);"
            "}"
        );

        // Add widgets to layout
        cardLayout->addWidget(title);
        cardLayout->addWidget(subtitle);
        cardLayout->addWidget(usernameEdit);
        cardLayout->addWidget(passwordEdit);
        cardLayout->addSpacing(12);
        cardLayout->addWidget(loginButton);

        // Signal
        connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    }

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;

    void handleLogin()
    {
        QString username = usernameEdit->text();
        QString password = passwordEdit->text();

        if(username == "admin" && password == "1234") {
            QMessageBox::information(this, "Login", "Login successful!");
        } else {
            QMessageBox::warning(this, "Login", "Invalid username or password");
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWindow window;
    window.show();

    return app.exec();
}