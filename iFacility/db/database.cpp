#include "database.h"

Database *Database::mInstance = new Database();
const QString Database::mFilename = "data.bin";

Database* Database::instance() {
    return Database::mInstance;
}

QVector<Profession> Database::professions() const {
    return mProfessions;
}

QVector<User> Database::users() const {
    return mUsers;
}

bool Database::addUser(User usr) {
    if (getUser(usr.getLogin()) != nullptr) {
        return false;
    }
    mUsers.push_back(usr);
    return true;
}

QVector<User*> Database::findUserByPredicat(UserPredicat predicat) {
    QVector<User*> out;
    auto it = mUsers.begin();
    while (it != mUsers.end()) {
        it = std::find_if(it, mUsers.end(), predicat);
        if (it != mUsers.end()) {
            out.push_back(it++);
        }
    }
    return out;
}

User* Database::getUser(UID uid) {
    auto pred = [uid](User u) { return u.uID() == uid; };
    auto users = findUserByPredicat(pred);
    return users.isEmpty()? nullptr : users[0];
}

User* Database::getUser(QString login) {
    auto pred = [login](User u) { return u.getLogin() == login; };
    auto users = findUserByPredicat(pred);
    return users.isEmpty()? nullptr : users[0];
}

QVector<User*> Database::getUsersByType(UserType type) {
    auto pred = [type](User u) { return u.getUserType() == type; };
    return findUserByPredicat(pred);
}

QVector<User*> Database::getUsersByProfession(PID pid) {
    auto pred = [pid](User u) { return u.hasProfession(pid); };
    return findUserByPredicat(pred);
}

bool Database::removeUser(UID uid) {
    auto prof = getUser(uid);
    if (prof == nullptr) {
        return false;
    }
    auto pred = [uid](User u) { return u.uID() == uid; };
    mUsers.erase(std::remove_if(mUsers.begin(), mUsers.end(), pred),
                 mUsers.end());
    return true;
}

bool Database::addProfession(Profession prof) {
    if (getProfession(prof.pID()) != nullptr) {
        return false;
    }
    mProfessions.push_back(prof);
    return true;
}

Profession* Database::getProfession(PID pid) {
    auto it = std::find_if(mProfessions.begin(), mProfessions.end(),
                           [pid](Profession p) { return p.pID() == pid; });
    return it == mProfessions.end()? nullptr : it;
}

bool Database::removeProfession(PID pid) {
    auto prof = getProfession(pid);
    if (prof == nullptr) {
        return false;
    }
    auto assignedUsers = getUsersByProfession(pid);
    if (!assignedUsers.isEmpty()) {
        return false;
    }
    auto pred = [pid](Profession p) { return p.pID() == pid; };
    mProfessions.erase(std::remove_if(mProfessions.begin(), mProfessions.end(), pred),
                       mProfessions.end());
    return true;
}

void Database::save() {
    QFile f(Database::mFilename);
    f.open(QIODevice::ReadOnly);
    QDataStream stream(&f);
    stream << mProfessions << mUsers;
    f.close();
}

void Database::load() {
    if (!QFile().exists(Database::mFilename)) {
        return;
    }
    mUsers.clear();
    mProfessions.clear();
    QFile f(Database::mFilename);
    f.open(QIODevice::WriteOnly);
    QDataStream stream(&f);
    stream >> mProfessions >> mUsers;
    f.close();
}
