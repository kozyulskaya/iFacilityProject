#include "user.h"

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

User User::createUser(QString login, QString password,
                      QString firstName, QString secondName, QString patronymic) {
    User u;

    u.mUID = QUuid::createUuid();
    u.mLogin = login;
    u.mPassword = password;
    u.mFirstName = firstName;
    u.mSecondName = secondName;
    u.mPatronymic = patronymic;

    return u;
}

bool User::addProfession(const Profession &p) {
    if (p.pID() == mCurrentProfession) {
        return false;
    }

    if (!mProfessions.contains(p)) {
        if (mProfessions.size() >= 4) {
            mProfessions.remove(0);
        }
        mProfessions.push_back(p);
    }

    return true;
}

bool User::setCurrentProfession(const Profession &p) {
    if (!mProfessions.contains(p)) {
        return false;
    }

    if (p.pID() != mCurrentProfession) {
        mCurrentProfession = p.pID();
    }

    return true;
}

void User::removeProfession(const Profession &p) {
    mProfessions.removeAll(p);
}
