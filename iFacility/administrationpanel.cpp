#include "administrationpanel.h"
#include "ui_administrationpanel.h"

AdministrationPanel::AdministrationPanel(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::AdministrationPanel) {
    ui->setupUi(this);

    connect(this, &AdministrationPanel::invalidateTables,
            this, &AdministrationPanel::onTablesInvalidation);

    avm = new AdministrationViewModel(this);
    ui->administrationView->setModel(avm);
    wvm = new WorkersViewModel(this);
    ui->workersView->setModel(wvm);
    pvm = new ProfessionsViewModel(this);
    ui->professionsView->setModel(pvm);

    emit invalidateTables();
}
\\*
**

AdministrationPanel::~AdministrationPanel() {
    delete ui;

    delete avm;
    delete wvm;
    delete pvm;
}

void AdministrationPanel::setUser(User *user) {
    mUser = user;
    ui->user->setText(tr("Привет, **%1**").arg(user->getFullNameShortForm()));
    ui->administrationGroup->setVisible(user->getUserType() == UserType::ADMINISTRATOR);
}

void AdministrationPanel::resizeEvent(QResizeEvent *event) {
    int cellWidth = 60;

    ui->administrationView->setColumnWidth(0, cellWidth*4);
    ui->administrationView->setColumnWidth(1, cellWidth*1);
    ui->administrationView->setColumnWidth(2, cellWidth*4);
    ui->administrationView->setColumnWidth(3, cellWidth*2);

    ui->workersView->setColumnWidth(0, cellWidth*4);
    ui->workersView->setColumnWidth(1, cellWidth*1);
    ui->workersView->setColumnWidth(2, cellWidth*4);
    ui->workersView->setColumnWidth(3, cellWidth*4);
    ui->workersView->setColumnWidth(4, cellWidth*4);
    ui->workersView->setColumnWidth(5, cellWidth*4);
    ui->workersView->setColumnWidth(6, cellWidth*4);

    QMainWindow::resizeEvent(event);
}

void AdministrationPanel::addAdministration() {
    QStringList items = {
        "Administrator",
        "Dispatcher"
    };
    bool ok;
    QString sel = QInputDialog::getItem(this, "Administration type", "", items, 0, false, &ok);
    if (ok) {
        UserType t = sel == "Administrator"? UserType::ADMINISTRATOR : UserType::DISPATCHER;
        User *user = new User();
        RegistrationDialog rd(this);
        rd.setEditMode(false);
        rd.setUser(user);
        rd.lockUserType(t);
        rd.setWindowTitle("New administration");
        if (rd.exec() == RegistrationDialog::Accepted) {
            Database::instance()->addUser(*user);
            emit invalidateTables();
            return;
        }
    }
    QMessageBox::critical(this, "Error", "Aborted by user");
}

void AdministrationPanel::addWorker() {
    User *user = new User();
    RegistrationDialog rd(this);
    rd.setEditMode(false);
    rd.setUser(user);
    rd.lockUserType(UserType::WORKER);
    rd.setWindowTitle("New worker");
    if (rd.exec() == RegistrationDialog::Accepted) {
        Database::instance()->addUser(*user);
        emit invalidateTables();
        return;
    }
}

void AdministrationPanel::addProfession() {
    QString title = QInputDialog::getText(this, "Input", "Profession title").trimmed();
    if (!title.isEmpty()) {
        Profession p = Profession::createProfession(title);
        bool ok = Database::instance()->addProfession(p);
        if (ok) {
            emit invalidateTables();
        }
        else {
            QMessageBox::critical(this, "Error", "You are trying to add the same job twice");
        }
        return;
    }
    QMessageBox::critical(this, "Error", "Aborted by user");
}

void AdministrationPanel::editAdministration() {
    auto rows = ui->administrationView->selectionModel()->selectedRows();
    if (rows.isEmpty() || rows.size() > 1) {
        return;
    }
    UID aUID = avm->index(rows[0].row(), 0).data().toString();
    if (aUID == mUser->uID()) {
        QMessageBox::critical(this, "Error", "You cannot edit yourself.");
        return;
    }
    editUser(aUID);
}

void AdministrationPanel::editWorker() {
    auto rows = ui->workersView->selectionModel()->selectedRows();
    if (rows.isEmpty() || rows.size() > 1) {
        return;
    }
    UID wUID = wvm->index(rows[0].row(), 0).data().toString();
    editUser(wUID);
}

void AdministrationPanel::editUser(UID uid) {
    User *user = Database::instance()->getUser(uid);
    if (user == nullptr) {
        QMessageBox::critical(this, "Error", "USer not found");
        return;
    }
    RegistrationDialog rd(this);
    rd.setEditMode(true);
    rd.setUser(user);
    rd.lockUserType(user->getUserType());
    rd.setWindowTitle("Edit user");
    if (rd.exec() == RegistrationDialog::Accepted) {
        Database::instance()->addUser(*user);
        emit invalidateTables();
    }
}

void AdministrationPanel::editProfession() {
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
        QString title = QInputDialog::getText(this, "Input", "New title").trimmed();
        if (!title.isEmpty()) {
            Database::instance()->getProfession(pid)->setTitle(title);
            emit invalidateTables();
            return;
        }
    }
    QMessageBox::critical(this, "Error", "Aborted by user");
}

void AdministrationPanel::removeAdministration() {
    auto rows = ui->administrationView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        return;
    }
    QMessageBox remconf(this);
    remconf.setIcon(QMessageBox::Question);
    remconf.setWindowTitle("Remove confirmation");
    remconf.setText("Are you sure you want to remove this worker?");
    remconf.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    remconf.setDefaultButton(QMessageBox::No);
    if (remconf.exec() == QMessageBox::No) {
        return;
    }
    for (int i = rows.size() - 1; i >= 0; i--) {
        UID aUID = avm->index(rows[i].row(), 0).data().toString();
        if (aUID == mUser->uID()) {
            QMessageBox::critical(this, "Error", "You cannot remove yourself.");
        }
        else {
            Database::instance()->removeUser(aUID);
        }
    }
    emit invalidateTables();
}

void AdministrationPanel::removeWorker() {
    auto rows = ui->workersView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        return;
    }
    QMessageBox remconf(this);
    remconf.setIcon(QMessageBox::Question);
    remconf.setWindowTitle("Remove confirmation");
    remconf.setText("Are you sure you want to remove this worker?");
    remconf.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    remconf.setDefaultButton(QMessageBox::No);
    if (remconf.exec() == QMessageBox::No) {
        return;
    }
    for (int i = rows.size() - 1; i >= 0; i--) {
        UID wUID = wvm->index(rows[i].row(), 0).data().toString();
        Database::instance()->removeUser(wUID);
    }
    emit invalidateTables();
}

void AdministrationPanel::removeProfession() {
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
        ok = Database::instance()->removeProfession(pid);
        if (ok) {
            emit invalidateTables();
            return;
        }
    }
    QMessageBox::critical(this, "Error", "Aborted by user or "
                                         "workers depend on selected profession");
}

void AdministrationPanel::onTablesInvalidation() {
    avm->invalidateData();
    wvm->invalidateData();
    pvm->invalidateData();
}
