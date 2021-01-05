#ifndef PROFESSIONSVIEMODEL_H
#define PROFESSIONSVIEMODEL_H

#include <QStandardItemModel>

#include "../db/database.h"

class ProfessionsViewModel : public QStandardItemModel {
private:
    Q_OBJECT

public:
    ProfessionsViewModel(QObject *parent);

    void invalidateData();
};

#endif // PROFESSIONSVIEMODEL_H
