#ifndef PROFESSION_H
#define PROFESSION_H

#include <QString>
#include <QUuid>
#include <QDataStream>

typedef QUuid PID;  //< Определение типа для UUID профессии

/**
 * @brief Класс сущности профессии
 * 
 */
class Profession {
private:
    //! UUID данной профессии
    PID mPID;
    //! Название данной профессии
    QString mTitle;

public:
    /**
    * @brief Стандартный конструктор объекта класса
    * 
    */
    Profession() = default;

    /**
     * @brief Метод получения названия профессии
     * 
     * @return QString название профессии
     */
    QString title() const;
    /**
     * @brief Установка нового названия профессии
     * 
     * @param newTitle новое название профессии
     */
    void setTitle(const QString &newTitle);
    /**
     * @brief Возвращает UUID профессии
     * 
     * @return PID UUID профессии
     */
    PID pID() const;

    /**
     * @brief Функция создания объекта профессии
     * 
     * @param title название профессии
     * @return Profession объект профессии
     */
    static Profession createProfession(const QString &title);

    /**
     * @brief Определения оператора сравнения для класса
     * 
     * @param l левый операнд
     * @param r правый операнд
     * @return true объекты идентичны
     * @return false объекты отличаются
     */
    friend bool operator==(const Profession &l, const Profession &r);
    /**
     * @brief Определение оператора ввода в поток
     * 
     * @param stream поток
     * @param prof объект класса
     * @return QDataStream& ссылка на поток
     */
    friend QDataStream& operator<<(QDataStream &stream, const Profession &prof);
    /**
     * @brief Определение оператора ввода из потока
     * 
     * @param stream поток
     * @param prof объект класса
     * @return QDataStream& ссылка на поток
     */
    friend QDataStream& operator>>(QDataStream &stream, Profession &prof);
};

#endif // PROFESSION_H
