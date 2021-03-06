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

QString User::getFullName() const {
    return QString("%1 %2 %3").arg(mSecondName).arg(mFirstName).arg(mPatronymic);
}

QString User::getFullNameShortForm() const {
    return QString("%1 %2.%3.").arg(mSecondName).arg(mFirstName[0]).arg(mPatronymic[0]);
}

ProfessionsList User::getProfessions() const {
    return mProfessions;
}

PID User::getCurrentProfession() const {
    return mCurrentProfession;
}

User* User::createUser(QString login, QString password, UserType userType,
                       QString firstName, QString secondName, QString patronymic) {
    User *u = new User();

    u->mUID = QUuid::createUuid();
    u->mLogin = login;
    u->mPassword = password;
    u->mUserType = userType;
    u->mFirstName = firstName;
    u->mSecondName = secondName;
    u->mPatronymic = patronymic;

    return u;
}

bool User::hasProfession(PID pid) {
    foreach (auto prof, mProfessions) {
        if (prof.getProfession() == pid) {
            return true;
        }
    }

    return false;
}

bool User::addProfession(PID pid, ProfRank rank) {
    if (hasProfession(pid)) {
        return false;
    }

    if (mProfessions.size() >= 4) {
        if (mCurrentProfession == mProfessions[0].getProfession()) {
            return false;
        }
        mProfessions.remove(0);
    }
    UserProfession up(pid, rank);

    mProfessions.push_back(up);
    return true;
}

bool User::setCurrentProfession(PID pid) {
    if (!hasProfession(pid)) {
        return false;
    }

    mCurrentProfession = pid;
    return true;
}

void User::removeProfession(PID pid) {
    auto pred = [pid](UserProfession p) { return p.getProfession() == pid; };
    if (pid == mCurrentProfession) {
        mCurrentProfession = 0;
    }
    mProfessions.erase(
                std::remove_if(mProfessions.begin(), mProfessions.end(), pred),
                mProfessions.end()
    );
}

bool operator==(const User &l, const User &r) {
    return l.mUID == r.mUID && l.mLogin == r.mLogin;
}

QDataStream& operator<<(QDataStream &stream, const User &usr) {
    stream << usr.mUID << usr.mUserType
           << usr.mLogin << usr.mPassword
           << usr.mFirstName << usr.mSecondName << usr.mPatronymic
           << usr.mProfessions << usr.mCurrentProfession;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, User &usr) {
    stream >> usr.mUID >> usr.mUserType
           >> usr.mLogin >> usr.mPassword
           >> usr.mFirstName >> usr.mSecondName >> usr.mPatronymic
           >> usr.mProfessions >> usr.mCurrentProfession;
    return stream;
}
