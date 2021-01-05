#ifndef WORKERPANEL_H
#define WORKERPANEL_H

#include <QMainWindow>

namespace Ui {
class WorkerPanel;
}

class WorkerPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit WorkerPanel(QWidget *parent = nullptr);
    ~WorkerPanel();

private:
    Ui::WorkerPanel *ui;
};

#endif // WORKERPANEL_H
