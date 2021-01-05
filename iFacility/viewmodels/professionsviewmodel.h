#ifndef PROFESSIONSVIEMODEL_H
#define PROFESSIONSVIEMODEL_H

#include <QStandardItemModel>

#include "../db/database.h"

/**
 * @brief ViewModel для дерева профессий
 * 
 */
class ProfessionsViewModel : public QStandardItemModel {
private:
    Q_OBJECT

public:
    /**
     * @brief Стандартный конструктор объекта класса
     * 
     * @param parent родитель, для определения периодов жизни ViewModel
     */
    ProfessionsViewModel(QObject *parent);

    /**
     * @brief Запускает перерисовку таблицы
     * 
     */
    void invalidateData();
};

#endif // PROFESSIONSVIEMODEL_H
