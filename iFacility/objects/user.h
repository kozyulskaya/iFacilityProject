#ifndef USER_H
#define USER_H

#include <QString>
#include <QUuid>
#include <QVector>
#include <QDate>

#include "profession.h"
#include "userprofession.h"

typedef QUuid UID;  //< Тип для UUID пользователя
typedef QVector<UserProfession> ProfessionsList;  //< Тип списка профессий пользователя

//! Набор возможных типов аккаунта пользователя
enum class UserType {
    ADMINISTRATOR = 0,  //< Указывает, что пользователь является администратором
    DISPATCHER = 1,  //< Указывает, что пользователя является диспетчером
    WORKER = 2  //< Указывает, что пользователь является рабочим
};

/**
 * @brief Класс сущности пользователя
 * 
 */
class User {
private:
    //! UUID данного пользователя
    UID mUID;
    //! Логин данного пользователя
    QString mLogin;
    //! Пароль данного пользователя
    QString mPassword;
    //! Тип аккаунта данного пользователя
    UserType mUserType;
    //! Имя данного пользователя
    QString mFirstName;
    //! Фамилия данного пользователя
    QString mSecondName;
    //! Отчество данного пользователя
    QString mPatronymic;
    //! Список профессий пользователя
    ProfessionsList mProfessions;
    //! UUID текущей профессии пользователя
    PID mCurrentProfession = 0;

    //! Объявляем, что класс \see RegistrationDialog является дружественным данному
    friend class RegistrationDialog;

public:
    /**
    * @brief Стандартный конструктор объекта класса
    * 
    */
    User() = default;

    /**
     * @brief Возвращает уникальный идентификатор пользователя
     * 
     * @return UID уникальный идентификатор пользователя
     */
    UID uID() const;
    /**
     * @brief Возвращает логин пользователя
     * 
     * @return QString логин пользователя
     */
    QString getLogin() const;
    /**
     * @brief Проверяет, совпадает ли \param password с текущим паролем пользователя
     * 
     * @param password проверяемый пароль
     * @return true пароли совпадают
     * @return false пароли не совпадают
     */
    bool checkPassword(const QString &password);
    /**
     * @brief Возвращает тип аккаунта пользователя
     * 
     * @return UserType тип аккаунта пользователя
     */
    UserType getUserType() const;
    /**
     * @brief Возвращает имя пользователя
     * 
     * @return QString имя пользоваетля
     */
    QString firstName() const;
    /**
     * @brief Возвращает фамилию пользователя
     * 
     * @return QString фамилия пользователя
     */
    QString secondName() const;
    /**
     * @brief Возвращает отчество пользователя
     * 
     * @return QString отчество пользователя
     */
    QString patronymic() const;
    /**
     * @brief Возвращает полное имя пользователя (Фамилия Имя Отчество)
     * 
     * @return QString полное имя пользователя
     */
    QString getFullName() const;
    /**
     * @brief Возвращает краткую форму полного имени пользователя (Фамилия И.О.)
     * 
     * @return QString краткая форма полного имени пользователя
     */
    QString getFullNameShortForm() const;
    /**
     * @brief Возвращает список профессий пользователя
     * 
     * @return ProfessionsList список профессий пользователя
     */
    ProfessionsList getProfessions() const;
    /**
     * @brief Возвращает уникальный идентификатор текущей профессии пользователя
     * 
     * @return PID уникальный идентификатор профессии
     */
    PID getCurrentProfession() const;

    /**
     * @brief Функция создания объекта пользователя
     * 
     * @param login логин пользователя
     * @param password пароль пользователя
     * @param userType тип аккаунта пользователя
     * @param firstName имя пользователя
     * @param secondName фамилия пользователя
     * @param patronymic отчество пользователя
     * @return User* указатель на объект нового пользователя
     */
    static User* createUser(QString login, QString password, UserType userType,
                           QString firstName, QString secondName, QString patronymic);

    /**
     * @brief Проверка, имеется и у пользователя профессия с данным \param pid
     * 
     * @param pid уникальный идентификатор интересующей профессии
     * @return true пользователь имеет данную профессию
     * @return false данная профессия у пользователя отсутствует
     */
    bool hasProfession(PID pid);
    /**
     * @brief Добавляет профессию в список пользователя, вытесняя самую старую
     * 
     * @param pid уникальный идентификатор профессии
     * @param rank разряд рабочего в данной профессии
     * @return true успех
     * @return false не успех (данная профессия уже есть или будет вытеснена текущая профессия)
     */
    bool addProfession(PID pid, ProfRank rank);
    /**
     * @brief Устанавливает текущую профессию пользователя по \param pid
     * 
     * @param pid уникальный идентификатор профессии
     * @return true успех
     * @return false не успех (не владеет данной профессией)
     */
    bool setCurrentProfession(PID pid);
    /**
     * @brief Убирает профессию с \param pid из списка профессий пользователя
     * 
     * @param pid 
     */
    void removeProfession(PID pid);

    /**
     * @brief Определения оператора сравнения для класса
     * 
     * @param l левый операнд
     * @param r правый операнд
     * @return true объекты идентичны
     * @return false объекты отличаются
     */
    friend bool operator==(const User &l, const User &r);
    /**
     * @brief Определение оператора ввода в поток
     * 
     * @param stream поток
     * @param usr объект класса
     * @return QDataStream& ссылка на поток
     */
    friend QDataStream& operator<<(QDataStream &stream, const User &usr);
    /**
     * @brief Определение оператора ввода из потока
     * 
     * @param stream поток
     * @param usr объект класса
     * @return QDataStream& ссылка на поток
     */
    friend QDataStream& operator>>(QDataStream &stream, User &usr);
};

#endif // USER_H
