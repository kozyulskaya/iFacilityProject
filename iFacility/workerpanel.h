#ifndef WORKERPANEL_H
#define WORKERPANEL_H

#include <QMainWindow>

#include "objects/user.h"
#include "viewmodels/userprofessionviewmodel.h"

namespace Ui { class WorkerPanel; }

class WorkerPanel : public QMainWindow {
private:
    Q_OBJECT

    Ui::WorkerPanel *ui;
    UserProfessionViewModel *upvm;
    User *mUser;

public:
    explicit WorkerPanel(QWidget *parent = nullptr);
    ~WorkerPanel();

    void setUser(User *user);
};

#endif // WORKERPANEL_H
