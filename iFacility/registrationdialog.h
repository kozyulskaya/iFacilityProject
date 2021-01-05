#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>

#include "objects/user.h"
#include "viewmodels/userprofessionviewmodel.h"

/**
 * @brief В данной неймспейсе QTFramework хранит MOC-объект, позволяющий работать с интерфейсом
 * 
 */
namespace Ui { class RegistrationDialog; }

/**
 * @brief Класс интерфейса диалога регистрации
 * 
 */
class RegistrationDialog : public QDialog {
private:
    Q_OBJECT

    //! Статический объект разметки интерфейса
    Ui::RegistrationDialog *ui;
    //! ViewModel для отображения прфоессий рабочего
    UserProfessionViewModel *upvm;
    //! Объект редактируемого (или создаваемого) пользователя
    User *user = nullptr;
    //! Флаг редактирования пользователя
    bool mEditMode = false;

public:
    /**
     * @brief Стандартный конструктор объекта интерфейса 
     * 
     * @param parent [ignored]
     */
    explicit RegistrationDialog(QWidget *parent = nullptr);
    /**
     * @brief Стандартный деструктор объекта интерфейса
     * 
     */
    ~RegistrationDialog();

    /**
     * @brief Блокирует поле выбора типа аккаунта в определённом положении \param type
     * 
     * @param type тип пользователя, который нужно установить и заблокировать
     */
    void lockUserType(UserType type);
    /**
     * @brief Устанавливает пользователя, коотрый будет редактироваться (или создаваться)
     * 
     * @param user указатель на объект пользователя
     */
    void setUser(User *usr);
    /**
     * @brief Устанавливает флаг редактирования пользователя
     * 
     * @param editMode 
     */
    void setEditMode(bool editMode);

public slots:
    /**
     * @brief Слот события подтверждающего закрытия диалога
     * 
     */
    void accept() Q_DECL_OVERRIDE;

    /**
     * @brief Слот события добавления новой профессии
     * 
     */
    void addNewProfession();
    /**
     * @brief Слот события установки текущей професии пользователя
     * 
     */
    void setCurrentProfession();
    /**
     * @brief Слот события удаления профессии
     * 
     */
    void removeOldProfession();
};

#endif // REGISTRATIONDIALOG_H
