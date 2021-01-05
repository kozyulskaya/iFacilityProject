#include "administrationviewmodel.h"

AdministrationViewModel::AdministrationViewModel(QObject *parent) : QAbstractTableModel(parent) {

}

int AdministrationViewModel::rowCount(const QModelIndex &/*parent*/) const {
    return mUserData.length();
}

int AdministrationViewModel::columnCount(const QModelIndex &/*parent*/) const {
    return 4;
}

QVariant AdministrationViewModel::headerData(int section, Qt::Orientation orientation,
                                             int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("UID");
        case 1:
            return QString("Login");
        case 2:
            return QString("Full name");
        case 3:
            return QString("Status");
        }
    }
    return QVariant();
}

QVariant AdministrationViewModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        auto usr = mUserData[index.row()];

        int col = index.column();
        switch (col) {
        case 0:
            return usr.uID();
        case 1:
            return usr.getLogin();
        case 2:
            return usr.getFullName();
        case 3:
            return usr.getUserType() == UserType::ADMINISTRATOR? "Administrator" : "Dispatcher";
        }

        return "UNKNOWN FIELD";
    }

    return QVariant();
}

void AdministrationViewModel::invalidateData() {
    beginResetModel();
    mUserData.clear();
    foreach (auto u, Database::instance()->getUsersByType(UserType::ADMINISTRATOR)) {
        mUserData += *u;
    }
    foreach (auto u, Database::instance()->getUsersByType(UserType::DISPATCHER)) {
        mUserData += *u;
    }
    endResetModel();
}
