#ifndef USER_H
#define USER_H

#include <QString>
#include <QUuid>
#include <QVector>

#include "profession.h"

typedef QUuid UID;
typedef QVector<PID> ProfessionsList;

enum class UserType {
    ADMINISTRATOR,
    DISPATCHER,
    WORKER
};

class User {
private:
    UID mUID;
    QString mLogin;
    QString mPassword;
    UserType mUserType;
    QString mFirstName;
    QString mSecondName;
    QString mPatronymic;
    ProfessionsList mProfessions;
    PID mCurrentProfession = 0;

public:
    User() = default;

    UID uID() const;
    QString getLogin() const;
    bool checkPassword(const QString &password);
    UserType getUserType() const;
    QString firstName() const;
    QString secondName() const;
    QString patronymic() const;
    ProfessionsList getProfessions() const;
    PID getCurrentProfession() const;

    static User createUser(QString login, QString password, UserType userType,
                           QString firstName, QString secondName, QString patronymic);

    bool addProfession(const Profession &p);
    bool setCurrentProfession(const Profession &p);
    void removeProfession(const Profession &p);

    friend bool operator==(const User &l, const User &r);
    friend QDataStream& operator<<(QDataStream &stream, const User &usr);
    friend QDataStream& operator>>(QDataStream &stream, User &usr);
};

#endif // USER_H
