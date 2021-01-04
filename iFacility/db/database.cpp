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

QVector<User*> Database::getUsersByProfession(Profession prof) {
    auto pred = [prof](User u) { return u.hasProfession(prof.pID()); };
    return findUserByPredicat(pred);
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
