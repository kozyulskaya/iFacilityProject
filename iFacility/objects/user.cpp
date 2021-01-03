#include "user.h"

UserType User::getUserType() const
{
    return mUserType;
}

UID User::uID() const {
    return mUID;
}

QString User::getLogin() const {
    return mLogin;
}

bool User::checkPassword(const QString &password) {
    return mPassword == password;
}

QString User::firstName() const {
    return mFirstName;
}

QString User::secondName() const {
    return mSecondName;
}

QString User::patronymic() const {
    return mPatronymic;
}

ProfessionsList User::getProfessions() const {
    return mProfessions;
}

PID User::getCurrentProfession() const {
    return mCurrentProfession;
}

User User::createUser(QString login, QString password, UserType userType,
                      QString firstName, QString secondName, QString patronymic) {
    User u;

    u.mUID = QUuid::createUuid();
    u.mLogin = login;
    u.mPassword = password;
    u.mUserType = userType;
    u.mFirstName = firstName;
    u.mSecondName = secondName;
    u.mPatronymic = patronymic;

    return u;
}

bool User::addProfession(const Profession &p) {
    if (p.pID() == mCurrentProfession) {
        return false;
    }

    if (!mProfessions.contains(p.pID())) {
        if (mProfessions.size() >= 4) {
            mProfessions.remove(0);
        }
        mProfessions.push_back(p.pID());
    }

    return true;
}

bool User::setCurrentProfession(const Profession &p) {
    if (!mProfessions.contains(p.pID())) {
        return false;
    }

    if (p.pID() != mCurrentProfession) {
        mCurrentProfession = p.pID();
    }

    return true;
}

void User::removeProfession(const Profession &p) {
    mProfessions.removeAll(p.pID());
}

bool operator==(const User &l, const User &r) {
    return l.mUID == r.mUID && l.mLogin == r.mLogin;
}

QDataStream& operator<<(QDataStream &stream, const User &usr) {
    stream << usr.mUID
           << usr.mLogin << usr.mPassword
           << usr.mFirstName << usr.mSecondName << usr.mPatronymic
           << usr.mProfessions << usr.mCurrentProfession;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, User &usr) {
    stream >> usr.mUID
           >> usr.mLogin >> usr.mPassword
           >> usr.mFirstName >> usr.mSecondName >> usr.mPatronymic
           >> usr.mProfessions >> usr.mCurrentProfession;
    return stream;
}
