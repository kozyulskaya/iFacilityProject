#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>

#include "objects/user.h"
#include "viewmodels/userprofessionviewmodel.h"

namespace Ui { class RegistrationDialog; }

class RegistrationDialog : public QDialog {
private:
    Q_OBJECT

    Ui::RegistrationDialog *ui;
    UserProfessionViewModel *upvm;
    User *user = nullptr;
    bool mEditMode = false;

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);
    ~RegistrationDialog();

    void lockUserType(UserType type);
    void setUser(User *usr);
    void setEditMode(bool editMode);

public slots:
    void accept() Q_DECL_OVERRIDE;

    void addNewProfession();
    void setCurrentProfession();
    void removeOldProfession();
};

#endif // REGISTRATIONDIALOG_H
