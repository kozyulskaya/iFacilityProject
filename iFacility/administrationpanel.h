#ifndef ADMINISTRATIONPANEL_H
#define ADMINISTRATIONPANEL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>

#include "objects/user.h"
#include "objects/profession.h"
#include "db/database.h"
#include "registrationdialog.h"
#include "viewmodels/administrationviewmodel.h"
#include "viewmodels/workersviewmodel.h"
#include "viewmodels/professionsviewmodel.h"

namespace Ui { class AdministrationPanel; }

class AdministrationPanel : public QMainWindow {
private:
    Q_OBJECT

    Ui::AdministrationPanel *ui;
    AdministrationViewModel *avm;
    WorkersViewModel *wvm;
    ProfessionsViewModel *pvm;
    User *mUser;

public:
    explicit AdministrationPanel(QWidget *parent = nullptr);
    ~AdministrationPanel();

    void setUser(User *user);

signals:
    void invalidateTables();

public slots:
    void resizeEvent(QResizeEvent *event);

    void doLogout();

    void addAdministration();
    void addWorker();
    void addProfession();

    void editAdministration();
    void editWorker();
    void editUser(UID uid);
    void editProfession();

    void removeAdministration();
    void removeWorker();
    void removeProfession();

    void onTablesInvalidation();
};

#endif // ADMINISTRATIONPANEL_H
