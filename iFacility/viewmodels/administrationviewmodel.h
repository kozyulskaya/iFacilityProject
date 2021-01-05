#ifndef ADMINISTRATIONVIEWMODEL_H
#define ADMINISTRATIONVIEWMODEL_H

#include <QAbstractTableModel>
#include <QVector>

#include "../objects/user.h"
#include "../db/database.h"

class AdministrationViewModel : public QAbstractTableModel {
private:
    Q_OBJECT

    QVector<User> mUserData;

public:
    AdministrationViewModel(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void invalidateData();
};

#endif // ADMINISTRATIONVIEWMODEL_H
