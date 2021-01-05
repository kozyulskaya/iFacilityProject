#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "objects/user.h"
#include "db/database.h"

#include "registrationdialog.h"
#include "administrationpanel.h"
#include "workerpanel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow {
private:
    Q_OBJECT

    Ui::LoginWindow *ui;

    void checkForFirstRun();
    void doLogin();

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

public slots:
    void validateForm();
};
#endif // LOGINWINDOW_H
