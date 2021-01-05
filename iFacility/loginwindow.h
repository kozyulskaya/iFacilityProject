#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "objects/user.h"
#include "db/database.h"

#include "registrationdialog.h"
#include "administrationpanel.h"
#include "workerpanel.h"

/**
 * @brief В данной неймспейсе QTFramework хранит MOC-объект, позволяющий работать с интерфейсом
 * 
 */
namespace Ui { class LoginWindow; }

/**
 * @brief Класс интерфейса панели авторизации
 * 
 */
class LoginWindow : public QMainWindow {
private:
    Q_OBJECT

    //! Статический объект разметки интерфейса
    Ui::LoginWindow *ui;

    /**
     * @brief Функция проверки и запуска соответствующих процедур при первом запуске ИС
     * 
     */
    void checkForFirstRun();
    /**
     * @brief Функция авторизации пользователя
     * 
     */
    void doLogin();

public:
    /**
     * @brief Стандартный конструктор объекта интерфейса 
     * 
     * @param parent [ignored]
     */
    LoginWindow(QWidget *parent = nullptr);
    /**
     * @brief Стандартный деструктор объекта интерфейса
     * 
     */
    ~LoginWindow();

public slots:
    /**
     * @brief Слот события валидации формы авторизации
     * 
     */
    void validateForm();
};
#endif // LOGINWINDOW_H
