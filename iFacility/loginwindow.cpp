#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    checkForFirstRun();
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::checkForFirstRun() {
    auto admins = Database::instance()->getUsersByType(UserType::ADMINISTRATOR);
    if (admins.isEmpty()) {
        QMessageBox::information(this, "Info", "No administrators found. "
                                               "Starting registration process.");
        User *user = new User();
        RegistrationDialog rd(this);
        rd.setEditMode(false);
        rd.setUser(user);
        rd.lockUserType(UserType::ADMINISTRATOR);
        rd.setWindowTitle("New administrator");
        if (rd.exec() != RegistrationDialog::Accepted) {
            QMessageBox::critical(this, "Error", "System cannot work without administrator "
                                                 "profile.\nPlease, restart application.");
            return;
        }

        Database::instance()->addUser(*user);
        QMessageBox::information(this, "Info", "Now you can login as administrator.");
    }
}

void LoginWindow::doLogin() {
    QString login = ui->login->text().trimmed();
    QString password = ui->password->text().trimmed();
    auto user = Database::instance()->getUser(login);
    if (user == nullptr || !user->checkPassword(password)) {
        QMessageBox::critical(this, "Error", "Wrong pair login/password");
        return;
    }

    QMessageBox::information(this, "Info", "Success");
    // TODO: Open valid window
}

void LoginWindow::validateForm() {
    if (ui->login->text().trimmed().isEmpty() || ui->password->text().trimmed().isEmpty()) {
        QMessageBox::critical(this, "Error", "Fields should not be empty");
        return;
    }

    doLogin();
}

