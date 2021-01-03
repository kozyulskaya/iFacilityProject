#ifndef USER_H
#define USER_H

#include <QString>
#include <QUuid>
#include <QVector>

#include "profession.h"

typedef QUuid UID;
typedef QVector<Profession> ProfessionsList;

class User {
private:
    UID mUID;
    QString mLogin;
    QString mPassword;
    QString mFirstName;
    QString mSecondName;
    QString mPatronymic;
    ProfessionsList mProfessions;
    PID mCurrentProfession = 0;

    User() = default;

public:
    UID uID() const;
    QString getLogin() const;
    bool checkPassword(const QString &password);
    QString firstName() const;
    QString secondName() const;
    QString patronymic() const;
    ProfessionsList getProfessions() const;
    PID getCurrentProfession() const;

    static User createUser(QString login, QString password,
                           QString firstName, QString secondName, QString patronymic);

    bool addProfession(const Profession &p);
    bool setCurrentProfession(const Profession &p);
    void removeProfession(const Profession &p);
};

#endif // USER_H
