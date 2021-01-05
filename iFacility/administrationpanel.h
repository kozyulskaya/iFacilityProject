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

/**
 * @brief В данной неймспейсе QTFramework хранит MOC-объект, позволяющий работать с интерфейсом
 * 
 */
namespace Ui { class AdministrationPanel; }

/**
 * @brief Класс интерфейса панели администрации
 * 
 */
class AdministrationPanel : public QMainWindow {
private:
    Q_OBJECT

    //! Статический объект разметки интерфейса
    Ui::AdministrationPanel *ui;
    //! ViewModel для отображения администрации системы
    AdministrationViewModel *avm;
    //! ViewModel для отображения рабочих системы
    WorkersViewModel *wvm;
    //! ViewModel для отображения префессий системы
    ProfessionsViewModel *pvm;
    //! Объект пользователя администрации
    User *mUser;

public:
    /**
     * @brief Стандартный конструктор объекта интерфейса 
     * 
     * @param parent [ignored]
     */
    explicit AdministrationPanel(QWidget *parent = nullptr);
    /**
     * @brief Стандартный деструктор объекта интерфейса
     * 
     */
    ~AdministrationPanel();

    /**
     * @brief Устанавливает пользователя, который в данный момент работает с панелью
     * 
     * @param user указатель на объект пользователя
     */
    void setUser(User *user);

signals:
    /**
     * @brief Сигнал, сообщающий о необходимости перерисовки таблиц
     * 
     */
    void invalidateTables();

public slots:
    /**
     * @brief Переопределение реакции на событие изменения размера. 
     *        Устанавливает ширину заголовков таблиц.
     * 
     * @param event [ignored]
     */
    void resizeEvent(QResizeEvent *event);

    /**
     * @brief Слот для события создания пользователя администрации
     * 
     */
    void addAdministration();
    /**
     * @brief Слот для события создания пользователя рабочего
     * 
     */
    void addWorker();
    /**
     * @brief Слот для события создания профессии
     * 
     */
    void addProfession();

    /**
     * @brief Слот для события редактирования пользователя администрации
     * 
     */
    void editAdministration();
    /**
     * @brief Слот для события редактирования пользователя рабочего
     * 
     */
    void editWorker();
    /**
     * @brief Общий слот для события редактирования пользователяпо его уникальному идентификатору
     * 
     */
    void editUser(UID uid);
    /**
     * @brief Слот для события редактирования профессии
     * 
     */
    void editProfession();

    /**
     * @brief Слот для события удаления пользователя администрации
     * 
     */
    void removeAdministration();
    /**
     * @brief Слот для события удаления пользователя рабочего
     * 
     */
    void removeWorker();
    /**
     * @brief Слот для события удаления профессии
     * 
     */
    void removeProfession();

    /**
     * @brief Слот для события запроса пеерисовки таблицы
     * 
     */
    void onTablesInvalidation();
};

#endif // ADMINISTRATIONPANEL_H
