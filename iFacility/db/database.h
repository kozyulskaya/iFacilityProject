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

typedef std::function<bool(User)> UserPredicat;

class Database {
private:
    static Database *mInstance;
    static const QString mFilename;

    Database() = default;
    QVector<Profession> mProfessions;
    QVector<User> mUsers;

    QVector<User*> findUserByPredicat(UserPredicat predicat);

public:
    static Database* instance();
    QVector<Profession> professions() const;
    QVector<User> users() const;

    bool addUser(User usr);
    User* getUser(UID uid);
    User* getUser(QString login);
    QVector<User*> getUsersByType(UserType type);
    QVector<User*> getUsersByProfession(PID pid);
    bool removeUser(UID uid);

    bool addProfession(Profession prof);
    Profession* getProfession(PID pid);
    bool removeProfession(PID pid);

    void save();
    void load();
};

#endif // DATABASE_H
