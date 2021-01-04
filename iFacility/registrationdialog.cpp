#include "registrationdialog.h"
#include "ui_registrationdialog.h"

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::RegistrationDialog) {
    ui->setupUi(this);

    upvm = new UserProfessionViewModel(this);
    ui->userProfessions->setModel(upvm);
}

RegistrationDialog::~RegistrationDialog() {
    delete ui;

    delete upvm;
}

void RegistrationDialog::lockUserType(UserType type) {
    ui->userGroup->setCurrentIndex((int)type);
    ui->userGroup->setEnabled(false);
}

void RegistrationDialog::setUser(User *usr) {
    user = usr;

    if (mEditMode) {
        ui->firstName->setText(user->firstName());
        ui->secondName->setText(user->secondName());
        ui->patronymic->setText(user->patronymic());
        ui->login->setText(user->getLogin());
        ui->login->setEnabled(false);
        ui->password->setText(user->mPassword);
        ui->password->setEnabled(usr->getUserType() == UserType::ADMINISTRATOR);
        ui->userGroup->setCurrentIndex((int)user->getUserType());
        ui->userGroup->setEnabled(false);
        upvm->setProfessionsList(user->getProfessions());
    }
}

void RegistrationDialog::setEditMode(bool editMode) {
    mEditMode = editMode;
}

void RegistrationDialog::accept() {
    QString fname = ui->firstName->text().trimmed();
    QString sname = ui->secondName->text().trimmed();
    QString patr = ui->patronymic->text().trimmed();
    QString login = ui->login->text().trimmed();
    QString pass = ui->password->text().trimmed();
    UserType type = (UserType)ui->userGroup->currentIndex();
    if (fname.isEmpty() || sname.isEmpty() || patr.isEmpty()
            || login.isEmpty() || pass.isEmpty()) {
        QMessageBox::critical(this, "Error", "Check field data correctness");
        return;
    }
    if (mEditMode) {
        QMessageBox::information(this, "Info", "Please note: login nor pasword cannot be "
                                               "changed. Your changes will be omited.");
        user->mPassword = pass;
        user->mFirstName = fname;
        user->mSecondName = sname;
        user->mPatronymic = patr;
    }
    else {
        auto u = User::createUser(login, pass, type, fname, sname, patr);
        std::swap(*user, *u);
        delete u;
    }

    QDialog::accept();
}

void RegistrationDialog::addNewProfession() {
    QStringList professions;
    foreach (auto prof, Database::instance()->professions()) {
        professions << prof.title() + "|" + prof.pID().toString();
    }
    if (professions.isEmpty()) {
        QMessageBox::critical(this, "Error", "No professions found");
        return;
    }
    bool ok;
    QString p = QInputDialog::getItem(this, "Choose profession", "Profession title",
                                      professions, 0, false, &ok);
    if (ok) {
        PID pid = p.split("|").last();
        int r = QInputDialog::getInt(this, "Profession rank", "", 1, 1, 2e5, 1, &ok);
        if (ok) {
            user->addProfession(pid, r);
            return;
        }
    }
    QMessageBox::critical(this, "Error", "Aborted by user or selected non-existant profession");
}

void RegistrationDialog::removeOldProfession() {

}
