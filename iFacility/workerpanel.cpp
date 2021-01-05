#include "workerpanel.h"
#include "ui_workerpanel.h"

WorkerPanel::WorkerPanel(QWidget *parent) : QMainWindow(parent), ui(new Ui::WorkerPanel) {
    ui->setupUi(this);

    upvm = new UserProfessionViewModel(this);
    ui->userProfessions->setModel(upvm);
    ui->userProfessions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

WorkerPanel::~WorkerPanel() {
    delete ui;

    delete upvm;
}

void WorkerPanel::setUser(User *usr) {
    mUser = usr;
    upvm->setUser(mUser);
    ui->user->setText(tr("Hello, **%1**").arg(mUser->getFullNameShortForm()));
}
