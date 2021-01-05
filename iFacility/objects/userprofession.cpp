#include "userprofession.h"

UserProfession::UserProfession(PID pid, ProfRank rank) {
    mProfession = pid;
    mRank = rank;
    mAcquired = QDate::currentDate();
}

PID UserProfession::getProfession() const {
    return mProfession;
}

QDate UserProfession::getAcquiredDate() const {
    return mAcquired;
}

ProfRank UserProfession::getRank() const {
    return mRank;
}

bool UserProfession::setRank(quint8 newRank) {
    if (newRank < 1) {
        return false;
    }

    mRank = newRank;
    return true;
}

bool operator==(const UserProfession &l, const UserProfession &r) {
    return  l.mProfession == r.mProfession &&
            l.mAcquired == r.mAcquired &&
            l.mRank == r.mRank;
}

QDataStream& operator<<(QDataStream &stream, const UserProfession &up) {
    stream << up.mProfession << up.mAcquired << up.mRank;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, UserProfession &up) {
    stream >> up.mProfession >> up.mAcquired >> up.mRank;
    return stream;
}
