#ifndef WORKERPANEL_H
#define WORKERPANEL_H

#include <QMainWindow>

#include "objects/user.h"
#include "viewmodels/userprofessionviewmodel.h"

/**
 * @brief В данной неймспейсе QTFramework хранит MOC-объект, позволяющий работать с интерфейсом
 * 
 */
namespace Ui { class WorkerPanel; }

/**
 * @brief Класс интерфейса панели рабочего
 * 
 */
class WorkerPanel : public QMainWindow {
private:
    Q_OBJECT

    //! Статический объект разметки интерфейса
    Ui::WorkerPanel *ui;
    //! ViewModel для отображения прфоессий рабочего
    UserProfessionViewModel *upvm;
    //! Объект пользователя рабочего
    User *mUser;

public:
    /**
     * @brief Стандартный конструктор объекта интерфейса 
     * 
     * @param parent [ignored]
     */
    explicit WorkerPanel(QWidget *parent = nullptr);
    /**
     * @brief Стандартный деструктор объекта интерфейса
     * 
     */
    ~WorkerPanel();

    /**
     * @brief Устанавливает пользователя, который в данный момент работает с панелью
     * 
     * @param user указатель на объект пользователя
     */
    void setUser(User *user);
};

#endif // WORKERPANEL_H
