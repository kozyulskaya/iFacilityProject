#include "workerpanel.h"
#include "ui_workerpanel.h"

WorkerPanel::WorkerPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WorkerPanel)
{
    ui->setupUi(this);
}

WorkerPanel::~WorkerPanel()
{
    delete ui;
}
