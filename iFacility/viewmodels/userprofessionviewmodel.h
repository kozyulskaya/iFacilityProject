#ifndef USERPROFESSIONVIEWMODEL_H
#define USERPROFESSIONVIEWMODEL_H

#include <QAbstractTableModel>

#include "../objects/user.h"
#include "../db/database.h"

class UserProfessionViewModel : public QAbstractTableModel {
private:
    Q_OBJECT

    ProfessionsList mProfList;

public:
    UserProfessionViewModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void setProfessionsList(const ProfessionsList &profList);
};

#endif // USERPROFESSIONVIEWMODEL_H
