#ifndef USER_H
#define USER_H

#include <QString>
#include <QUuid>
#include <QVector>
#include <QDate>

#include "profession.h"
#include "userprofession.h"

typedef QUuid UID;
typedef QVector<UserProfession> ProfessionsList;

enum class UserType {
    ADMINISTRATOR = 0,
    DISPATCHER = 1,
    WORKER = 2
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

    friend class RegistrationDialog;

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

    static User* createUser(QString login, QString password, UserType userType,
                           QString firstName, QString secondName, QString patronymic);

    bool hasProfession(PID pid);
    bool addProfession(PID pid, ProfRank rank);
    bool setCurrentProfession(PID pid);
    void removeProfession(PID pid);

    friend bool operator==(const User &l, const User &r);
    friend QDataStream& operator<<(QDataStream &stream, const User &usr);
    friend QDataStream& operator>>(QDataStream &stream, User &usr);
};

#endif // USER_H
