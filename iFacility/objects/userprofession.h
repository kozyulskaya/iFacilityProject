#ifndef USERPROFESSION_H
#define USERPROFESSION_H

#include <QDate>

#include "profession.h"

typedef quint8 ProfRank;

class UserProfession {
private:
    PID mProfession;
    QDate mAcquired;
    ProfRank mRank;

public:
    UserProfession() = default;
    UserProfession(PID pid, ProfRank rank);

    PID getProfession() const;
    QDate getAcquiredDate() const;
    ProfRank getRank() const;
    bool setRank(quint8 newRank);

    friend bool operator==(const UserProfession &l, const UserProfession &r);
    friend QDataStream& operator<<(QDataStream &stream, const UserProfession &up);
    friend QDataStream& operator>>(QDataStream &stream, UserProfession &up);
};

#endif // USERPROFESSION_H
