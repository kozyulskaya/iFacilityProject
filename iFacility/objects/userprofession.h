#ifndef USERPROFESSION_H
#define USERPROFESSION_H

#include <QDate>

#include "profession.h"

typedef quint8 ProfRank;  //< Тип для разряда владельца профессии

/**
 * @brief Класс-обёртка сущности профессии 
 * 
 * Используется для хранения соответствия между пользователем, его профессией и разрядом
 */
class UserProfession {
private:
    //! Уникальный идентификатор профессии
    PID mProfession;
    //! Дата получения профессии пользователем
    QDate mAcquired;
    //! Разряд профессии пользователя
    ProfRank mRank;

public:
    /**
    * @brief Стандартный конструктор объекта класса
    * 
    */
    UserProfession() = default;
    /**
     * @brief Конструктор объекта пользователя из \param pid профессии и разряда
     * 
     * @param pid уникальный идентификатор профессии
     * @param rank разряд профессии пользоваетля
     */
    UserProfession(PID pid, ProfRank rank);

    /**
     * @brief Возвращает идентификатор соотносимой професии
     * 
     * @return PID уникальный идентификатор професии
     */
    PID getProfession() const;
    /**
     * @brief Возвращает дату получения профессии
     * 
     * @return QDate дата получения професии
     */
    QDate getAcquiredDate() const;
    /**
     * @brief Возвращает разряд пользователя
     * 
     * @return ProfRank разряд пользователя
     */
    ProfRank getRank() const;
    /**
     * @brief Устанавливает разряд данной профессии пользователя
     * 
     * @param newRank новый разряд пользователя
     * @return true успех
     * @return false не успех (значение \param newRank < 1)
     */
    bool setRank(quint8 newRank);

    /**
     * @brief Определения оператора сравнения для класса
     * 
     * @param l левый операнд
     * @param r правый операнд
     * @return true объекты идентичны
     * @return false объекты отличаются
     */
    friend bool operator==(const UserProfession &l, const UserProfession &r);
    /**
     * @brief Определение оператора ввода в поток
     * 
     * @param stream поток
     * @param up объект класса
     * @return QDataStream& ссылка на поток
     */
    friend QDataStream& operator<<(QDataStream &stream, const UserProfession &up);
    /**
     * @brief Определение оператора ввода из потока
     * 
     * @param stream поток
     * @param up объект класса
     * @return QDataStream& ссылка на поток
     */
    friend QDataStream& operator>>(QDataStream &stream, UserProfession &up);
};

#endif // USERPROFESSION_H
