#ifndef DATABASE_H
#define DATABASE_H

#include <algorithm>
#include <functional>

#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QString>

#include "../objects/profession.h"
#include "../objects/user.h"

typedef std::function<bool(User)> UserPredicat;  //< Тип функции-предиката для фильтров и удаления

/**
 * @brief Класс базы данных
 * 
 * Данный класс позволяет получать доступ к данным системы (пользователям, профессиям)
 */
class Database {
private:
    //! Статический объект класса
    static Database *mInstance;
    //! Статическая константа, содержащая путь до файла сохранения данных
    static const QString mFilename;

    /**
     * @brief Стандартный конструктор класс
     * 
     * Сделан приватным, чтобы никто снаружи не мог создавать объекты данного класса
     */
    Database() = default;

    //! Список всех профессий системы
    QVector<Profession> mProfessions;
    //! Список всех пользователей системы
    QVector<User> mUsers;

    /**
     * @brief Функция поиска пользователя с использованием предиката
     * 
     * @param predicat функция-предикат
     * @return QVector<User*> список указателей на пользователей, соответствующих предикату
     */
    QVector<User*> findUserByPredicat(UserPredicat predicat);

public:
    /**
     * @brief Возвращает статический объекта класса
     * 
     * @return Database* указатель на статический объект класса
     */
    static Database* instance();
    /**
     * @brief Возвращает список профессий системы
     * 
     * @return QVector<Profession> список профессий системы
     */
    QVector<Profession> professions() const;
    /**
     * @brief Возвращает список пользователй системы
     * 
     * @return QVector<User> список пользователей системы
     */
    QVector<User> users() const;

    /**
     * @brief Добавляет пользователя в систему
     * 
     * @param usr новый пользователь
     * @return true успех
     * @return false не успех (пользователь уже есть в системе)
     */
    bool addUser(User usr);
    /**
     * @brief Возвращает пользователя по уникальному идентификатору \param uid
     * 
     * @param uid уникальный идентификатор пользователя
     * @return User* указатель на объект пользователя
     */
    User* getUser(UID uid);
    /**
     * @brief Возвращает пользователя по его логину \param login
     * 
     * @param login логин пользователя
     * @return User* указатель на объект пользователя
     */
    User* getUser(QString login);
    /**
     * @brief Возвращает список пользователей по типу аккаунта \param type
     * 
     * @param type тип аккаунта пользователя
     * @return QVector<User*> список указателей на объекты пользователей
     */
    QVector<User*> getUsersByType(UserType type);
    /**
     * @brief Возвращает список пользователей по принадлежности к профессии
     * 
     * @param pid уникальный идентификатор профессии
     * @return QVector<User*> список указателей на объекты пользователей
     */
    QVector<User*> getUsersByProfession(PID pid);
    /**
     * @brief Удалаяет пользователя из системы по уникальному идентификатору \param uid
     * 
     * @param uid уникальный идентификатор пользователя
     * @return true успех
     * @return false не успех (пользователя не существует)
     */
    bool removeUser(UID uid);

    /**
     * @brief Добавляет профессию в систему
     * 
     * @param prof новая профессия
     * @return true успех
     * @return false не успех (профессия существует)
     */
    bool addProfession(Profession prof);
    /**
     * @brief Возвращает профессию по уникальному идентификатору \param pid
     * 
     * @param pid уникальный идентификатор профессии
     * @return Profession* указатель на объект профессий
     */
    Profession* getProfession(PID pid);
    /**
     * @brief Удаляет профессию из системы по уникальному идентификатору \param pid
     * 
     * @param pid уникальынй идентификатор профессии
     * @return true успех
     * @return false не успех (профессии не существует или есть зависимые пользователи)
     */
    bool removeProfession(PID pid);

    /**
     * @brief Считывает данный с диска в систему
     * 
     */
    void save();
    /**
     * @brief Записывает данные системы на диск
     * 
     */
    void load();
};

#endif // DATABASE_H
