#include <QtTest>

#include <QByteArray>
#include <QDataStream>

#include "../iFacility/objects/profession.h"
#include "../iFacility/objects/user.h"

class iFacilityTest : public QObject {
private:
    Q_OBJECT

public:
    iFacilityTest() = default;
    ~iFacilityTest() = default;

private slots:
    void test_user_add_profession();
    void test_user_remove_profession();
    void test_user_current_profession();
    void test_user_serialization();

};



void iFacilityTest::test_user_add_profession() {
    auto u = User::createUser("test", "test", "f", "s", "t");

    auto p1 = Profession::createProfession("test1");
    auto p2 = Profession::createProfession("test2");
    auto p3 = Profession::createProfession("test3");
    auto p4 = Profession::createProfession("test4");
    auto p5 = Profession::createProfession("test5");

    u.addProfession(p1);
    QVERIFY(u.getProfessions().size() == 1);

    u.addProfession(p1);
    QVERIFY(u.getProfessions().size() == 1);

    u.addProfession(p2);
    u.addProfession(p3);
    u.addProfession(p4);
    u.addProfession(p5);
    QVERIFY(u.getProfessions().front() == p2.pID());
    QVERIFY(u.getProfessions().back() == p5.pID());
}

void iFacilityTest::test_user_remove_profession() {
    auto u = User::createUser("test", "test", "f", "s", "t");

    auto p1 = Profession::createProfession("test1");

    u.addProfession(p1);
    QVERIFY(u.getProfessions().size() == 1);

    u.removeProfession(p1);
    QVERIFY(u.getProfessions().isEmpty());
}

void iFacilityTest::test_user_current_profession() {
    auto u = User::createUser("test", "test", "f", "s", "t");

    auto p1 = Profession::createProfession("test1");
    auto p2 = Profession::createProfession("test2");

    u.addProfession(p1);

    QVERIFY(!u.setCurrentProfession(p2));
    QVERIFY(u.setCurrentProfession(p1));
    QVERIFY(u.getCurrentProfession() == p1.pID());
}

void iFacilityTest::test_user_serialization() {
    QByteArray bytes;
    QDataStream qdsw(&bytes, QIODevice::WriteOnly);
    QDataStream qdsr(&bytes, QIODevice::ReadOnly);

    auto u1 = User::createUser("test", "test", "f", "s", "t");

    auto p1 = Profession::createProfession("test1");
    auto p2 = Profession::createProfession("test2");

    u1.addProfession(p1);
    u1.addProfession(p2);
    u1.setCurrentProfession(p1);

    qdsw << u1;

    User u2;
    qdsr >> u2;

    QVERIFY(u1 == u2);
    QVERIFY(u1.getProfessions() == u2.getProfessions());
    QVERIFY(u1.getCurrentProfession() == u2.getCurrentProfession());
}

QTEST_APPLESS_MAIN(iFacilityTest)

#include "tst_ifacilitytest.moc"
