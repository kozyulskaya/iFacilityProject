#include "registrationdialog.h"
#include "ui_registrationdialog.h"

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::RegistrationDialog) {
    ui->setupUi(this);

    upvm = new UserProfessionViewModel(this);
    ui->userProfessions->setModel(upvm);

    connect(ui->userProfessions->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            [this]() {
                auto rows = ui->userProfessions->selectionModel()->selectedRows();
                ui->btnSetProfessionCurrent->setEnabled(rows.size() == 1);
                ui->btnRemoveProfession->setEnabled(rows.size() >= 1);
            }
    );

    connect(ui->userGroup,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int newIdx) {
                ui->professionsGroup->setVisible((UserType)newIdx == UserType::WORKER);
            }
    );
}

RegistrationDialog::~RegistrationDialog() {
    delete ui;

    delete upvm;
}

void RegistrationDialog::lockUserType(UserType type) {
    ui->userGroup->setCurrentIndex((int)type);
    ui->userGroup->setEnabled(false);
    ui->professionsGroup->setVisible(type == UserType::WORKER);
}

void RegistrationDialog::setUser(User *usr) {
    user = usr;
    upvm->setUser(user);

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
        u->mProfessions = user->mProfessions;
        u->setCurrentProfession(user->getCurrentProfession());
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
            upvm->invalidateData();
            return;
        }
    }
    QMessageBox::critical(this, "Error", "Aborted by user or selected non-existant profession");
}

void RegistrationDialog::setCurrentProfession() {
    auto rows = ui->userProfessions->selectionModel()->selectedRows();
    if (rows.isEmpty() || rows.size() > 1) {
        return;
    }
    auto uProf = user->getProfessions()[rows[0].row()];
    user->setCurrentProfession(uProf.getProfession());
    upvm->invalidateData();
}

void RegistrationDialog::removeOldProfession() {
    auto rows = ui->userProfessions->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        return;
    }
    QMessageBox remconf(this);
    remconf.setIcon(QMessageBox::Question);
    remconf.setWindowTitle("Remove confirmation");
    remconf.setText("Are you sure you want to remove this profession?");
    remconf.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    remconf.setDefaultButton(QMessageBox::No);
    if (remconf.exec() == QMessageBox::No) {
        return;
    }
    for (int i = rows.size() - 1; i >= 0; i--) {
        user->removeProfession(user->getProfessions()[rows[i].row()].getProfession());
    }
    upvm->invalidateData();
}
