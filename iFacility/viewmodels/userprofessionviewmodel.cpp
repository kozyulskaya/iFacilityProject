#include "userprofessionviewmodel.h"

UserProfessionViewModel::UserProfessionViewModel(QObject *parent) : QAbstractTableModel(parent) {

}

int UserProfessionViewModel::rowCount(const QModelIndex &/*parent*/) const {
    return mUser != nullptr? mUser->getProfessions().length() : 0;
}

int UserProfessionViewModel::columnCount(const QModelIndex &/*parent*/) const {
    return 3;
}

QVariant UserProfessionViewModel::headerData(int section,
                                             Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Profession");
        case 1:
            return QString("Acquisition date");
        case 2:
            return QString("Rank");
        }
    }
    return QVariant();
}

QVariant UserProfessionViewModel::data(const QModelIndex &index, int role) const {
    auto profs = mUser->getProfessions();
    auto uProf = profs[index.row()];

    if (role == Qt::DisplayRole) {
        auto prof = Database::instance()->getProfession(uProf.getProfession());

        int col = index.column();
        switch (col) {
        case 0:
            return prof == nullptr? "#ERROR!" : prof->title();
        case 1:
            return uProf.getAcquiredDate().toString(Qt::DateFormat::SystemLocaleShortDate);
        case 2:
            return uProf.getRank();
        }

        return "UNKNOWN FIELD";
    }
    else if (role == Qt::FontRole) {
        if (uProf.getProfession() == mUser->getCurrentProfession()) {
            QFont f;
            f.setBold(true);
            return f;
        }
    }

    return QVariant();
}

void UserProfessionViewModel::setUser(User *user) {
    mUser = user;
    invalidateData();
}

void UserProfessionViewModel::invalidateData() {
    beginResetModel();
    endResetModel();
}
