#ifndef ADMINISTRATIONVIEWMODEL_H
#define ADMINISTRATIONVIEWMODEL_H

#include <QAbstractTableModel>
#include <QVector>

#include "../objects/user.h"
#include "../db/database.h"

/**
 * @brief ViewModel для таблицы администрации (администраторы, диспетчеры)
 * 
 */
class AdministrationViewModel : public QAbstractTableModel {
private:
    Q_OBJECT

    //! Список администрации 
    QVector<User> mUserData;

public:
    /**
     * @brief Стандартный конструктор объекта класса
     * 
     * @param parent родитель, для определения периодов жизни ViewModel
     */
    AdministrationViewModel(QObject *parent);

    /**
     * @brief Возвращает кол-во строк в таблице
     * 
     * @param parent [ignored]
     * @return int кол-во строк в таблице
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @brief Возвращает кол-во столбцов в таблице
     * 
     * @param parent [ignored]
     * @return int кол-во столбцов в таблице
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @brief Возвращает содержимое заголовка таблицы
     * 
     * @param section [ignored]
     * @param orientation положение заголовка таблицы
     * @param role [ignored]
     * @return QVariant содержимое заголовка
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /**
     * @brief Возвращает содержимое ячеек таблицы
     * 
     * @param index индекс текущей ячейки
     * @param role какая часть таблицы отрисовывается (данные, стили и т.д.)
     * @return QVariant содержимое ячейки
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /**
     * @brief Запускает перерисовку таблицы
     * 
     */
    void invalidateData();
};

#endif // ADMINISTRATIONVIEWMODEL_H
