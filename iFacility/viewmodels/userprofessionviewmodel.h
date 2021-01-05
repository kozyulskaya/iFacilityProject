#ifndef USERPROFESSIONVIEWMODEL_H
#define USERPROFESSIONVIEWMODEL_H

#include <QAbstractTableModel>
#include <QFont>

#include "../objects/user.h"
#include "../db/database.h"

/**
 * @brief ViewModel для таблицы профессий пользователя
 * 
 */
class UserProfessionViewModel : public QAbstractTableModel {
private:
    Q_OBJECT

    /**
     * @brief Ссылка на объект пользователя, профессии которые будут отображаться
     * 
     * @param user 
     */
    User *mUser = nullptr;

public:
    /**
     * @brief Стандартный конструктор объекта класса
     * 
     * @param parent родитель, для определения периодов жизни ViewModel
     */
    UserProfessionViewModel(QObject *parent);

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
     * @brief Устанавливает пользователя, профессии которые будут отображаться
     * 
     * @param user 
     */
    void setUser(User *user);
    /**
     * @brief Запускает перерисовку таблицы
     * 
     */
    void invalidateData();
};

#endif // USERPROFESSIONVIEWMODEL_H
