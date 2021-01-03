#include "profession.h"

QString Profession::title() const {
    return mTitle;
}

PID Profession::pID() const {
    return mPID;
}

Profession Profession::createProfession(const QString &title) {
    Profession p;

    p.mPID = QUuid::createUuid();
    p.mTitle = title;

    return p;
}

bool operator==(const Profession &l, const Profession &r) {
    return l.mPID == r.mPID;
}

QDataStream& operator<<(QDataStream &stream, const Profession &prof) {
    stream << prof.mPID << prof.mTitle;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Profession &prof) {
    stream >> prof.mPID >> prof.mTitle;
    return stream;
}
