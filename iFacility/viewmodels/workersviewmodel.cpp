#include "workersviewmodel.h"

WorkersViewModel::WorkersViewModel(QObject *parent) : QAbstractTableModel(parent) {

}

int WorkersViewModel::rowCount(const QModelIndex &/*parent*/) const {
    return mUserData.length();
}

int WorkersViewModel::columnCount(const QModelIndex &/*parent*/) const {
    return 7;
}

QVariant WorkersViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("UID");
        case 1:
            return QString("Login");
        case 2:
            return QString("Full name");
        case 3:
            return QString("First profession");
        case 4:
            return QString("Second profession");
        case 5:
            return QString("Third profession");
        case 6:
            return QString("Fourth profession");
        }
    }
    return QVariant();
}

QString WorkersViewModel::getProfessionAt(const User &user, int pIdx) const {
    auto profs = user.getProfessions();
    QString out = "";
    if (profs.size() >= pIdx + 1) {
        auto p = Database::instance()->getProfession(profs[pIdx].getProfession());
        out = tr("%1 (%2 rank)").arg(p->title()).arg(profs[pIdx].getRank());
    }
    return out;
}

bool WorkersViewModel::shouldBeBold(const QModelIndex &index) const {
    int col = index.column();
    if (col < 3) {
        return false;
    }
    auto usr = mUserData[index.row()];
    if (!getProfessionAt(usr, col-3).isEmpty()) {
        if (usr.getProfessions()[col-3].getProfession() == usr.getCurrentProfession()) {
            return true;
        }
    }
    return false;
}

QVariant WorkersViewModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        auto usr = mUserData[index.row()];
        auto profs = usr.getProfessions();

        int col = index.column();
        switch (col) {
        case 0:
            return usr.uID();
        case 1:
            return usr.getLogin();
        case 2:
            return usr.getFullName();
        case 3:
            return getProfessionAt(usr, 0);
        case 4:
            return getProfessionAt(usr, 1);
        case 5:
            return getProfessionAt(usr, 2);
        case 6:
            return getProfessionAt(usr, 3);
        }

        return "UNKNOWN FIELD";
    }
    else if (role == Qt::FontRole) {
        if (shouldBeBold(index)) {
            QFont f;
            f.setBold(true);
            return f;
        }
    }
    return QVariant();
}

void WorkersViewModel::invalidateData() {
    beginResetModel();
    mUserData.clear();
    foreach (auto u, Database::instance()->getUsersByType(UserType::WORKER)) {
        mUserData += *u;
    }
    endResetModel();
}
