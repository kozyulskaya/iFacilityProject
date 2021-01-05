#ifndef WORKERSVIEWMODEL_H
#define WORKERSVIEWMODEL_H

#include <QAbstractTableModel>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QVector>

#include "../objects/user.h"
#include "../db/database.h"

/**
 * @brief ViewModel для таблицы рабочих
 * 
 */
class WorkersViewModel : public QAbstractTableModel {
private:
    Q_OBJECT

    //! Список рабочих
    QVector<User> mUserData;

    /**
     * @brief Возвращает строковое представление профессии пользователя по индексу \param pIdx
     * 
     * @param user пользовател
     * @param pIdx индекс профессии
     * @return QString строковое представление профессии
     */
    QString getProfessionAt(const User &user, int pIdx) const;
    /**
     * @brief Возвращает флаг, должна ли клетка таблицы иметь полужирный шрифт
     * 
     * @param index индекс модели
     * @return true должен быть полужирным
     * @return false не должен быть полужирным
     */
    bool shouldBeBold(const QModelIndex &index) const;

public:
    /**
     * @brief Стандартный конструктор объекта класса
     * 
     * @param parent родитель, для определения периодов жизни ViewModel
     */
    WorkersViewModel(QObject *parent);

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

#endif // WORKERSVIEWMODEL_H
