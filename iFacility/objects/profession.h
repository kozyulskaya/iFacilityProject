#ifndef PROFESSION_H
#define PROFESSION_H

#include <QString>
#include <QUuid>
#include <QDataStream>

typedef QUuid PID;

class Profession {
private:
    PID mPID;
    QString mTitle;

    Profession() = default;

public:
    QString title() const;
    PID pID() const;

    static Profession createProfession(const QString &title);

    friend bool operator==(const Profession &l, const Profession &r);
    friend QDataStream& operator<<(QDataStream &stream, const Profession &prof);
    friend QDataStream& operator>>(QDataStream &stream, Profession &prof);
};

#endif // PROFESSION_H
