#include "userprofessionviewmodel.h"

UserProfessionViewModel::UserProfessionViewModel(QObject *parent) : QAbstractTableModel(parent) {

}

int UserProfessionViewModel::rowCount(const QModelIndex &/*parent*/) const {
    return mProfList.length();
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
                return QString("Date of acquirement");
            case 2:
                return QString("Rank");
        }
    }
    return QVariant();
}

QVariant UserProfessionViewModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        auto item = mProfList[index.row()];
        auto prof = Database::instance()->getProfession(item.getProfession());

        int col = index.column();
        switch (col) {
            case 0:
                return prof == nullptr? "ERROR:UNKNOWN" : prof->title();
            case 1:
                return item.getAcquiredDate();
            case 2:
                return item.getRank();
        }

        return "UNKNOWN FIELD";
    }

    return QVariant();
}

void UserProfessionViewModel::setProfessionsList(const ProfessionsList &profList) {
    beginResetModel();
    mProfList.clear();
    mProfList += profList;
    endResetModel();
}
