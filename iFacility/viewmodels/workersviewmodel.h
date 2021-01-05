#ifndef WORKERSVIEWMODEL_H
#define WORKERSVIEWMODEL_H

#include <QAbstractTableModel>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QVector>

#include "../objects/user.h"
#include "../db/database.h"

class WorkersViewModel : public QAbstractTableModel {
private:
    Q_OBJECT

    QVector<User> mUserData;

    QString getProfessionAt(const User &user, int pIdx) const;
    bool shouldBeBold(const QModelIndex &index) const;

public:
    WorkersViewModel(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void invalidateData();
};

#endif // WORKERSVIEWMODEL_H
