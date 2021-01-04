#include <QtTest>

#include <QByteArray>
#include <QDataStream>

#include "../iFacility/objects/userprofession.h"
#include "../iFacility/objects/profession.h"
#include "../iFacility/objects/user.h"
#include "../iFacility/db/database.h"

class iFacilityTest : public QObject {
private:
    Q_OBJECT

    User sampleUser;
    Profession sampleProfession;

public:
    iFacilityTest() = default;
    ~iFacilityTest() = default;

private slots:
    void test_user_add_profession();
    void test_user_remove_profession();
    void test_user_current_profession();
    void test_user_serialization();

    void test_db_add_user();
    void test_db_get_user_by_uid();
    void test_db_get_user_by_login();
    void test_db_get_users_by_type();
    void test_db_get_users_gy_profession();
    void test_db_remove_dependant_profession();
    void test_db_remove_user();
    void test_db_remove_independant_profession();
};



void iFacilityTest::test_user_add_profession() {
    auto u = User::createUser("test", "test", UserType::ADMINISTRATOR, "f", "s", "t");

    auto p1 = Profession::createProfession("test1");
    auto p2 = Profession::createProfession("test2");
    auto p3 = Profession::createProfession("test3");
    auto p4 = Profession::createProfession("test4");
    auto p5 = Profession::createProfession("test5");

    u->addProfession(p1.pID(), 2);
    QVERIFY(u->getProfessions().size() == 1);

    u->addProfession(p1.pID(), 2);
    QVERIFY(u->getProfessions().size() == 1);

    u->addProfession(p2.pID(), 2);
    u->addProfession(p3.pID(), 2);
    u->addProfession(p4.pID(), 2);
    u->addProfession(p5.pID(), 2);
    QVERIFY(u->getProfessions().front().getProfession() == p2.pID());
    QVERIFY(u->getProfessions().back().getProfession() == p5.pID());
}

void iFacilityTest::test_user_remove_profession() {
    auto u = User::createUser("test", "test", UserType::ADMINISTRATOR, "f", "s", "t");

    auto p1 = Profession::createProfession("test1");

    u->addProfession(p1.pID(), 2);
    QVERIFY(u->getProfessions().size() == 1);

    u->removeProfession(p1.pID());
    QVERIFY(u->getProfessions().isEmpty());
}

void iFacilityTest::test_user_current_profession() {
    auto u = User::createUser("test", "test", UserType::ADMINISTRATOR, "f", "s", "t");

    auto p1 = Profession::createProfession("test1");
    auto p2 = Profession::createProfession("test2");

    u->addProfession(p1.pID(), 2);

    QVERIFY(!u->setCurrentProfession(p2.pID()));
    QVERIFY(u->setCurrentProfession(p1.pID()));
    QVERIFY(u->getCurrentProfession() == p1.pID());
}

void iFacilityTest::test_user_serialization() {
    QByteArray bytes;
    QDataStream qdsw(&bytes, QIODevice::WriteOnly);
    QDataStream qdsr(&bytes, QIODevice::ReadOnly);

    auto u1 = *User::createUser("test", "test", UserType::ADMINISTRATOR, "f", "s", "t");

    auto p1 = Profession::createProfession("test1");
    auto p2 = Profession::createProfession("test2");

    u1.addProfession(p1.pID(), 2);
    u1.addProfession(p2.pID(), 2);
    u1.setCurrentProfession(p1.pID());

    qdsw << u1;

    User u2;
    qdsr >> u2;

    QVERIFY(u1 == u2);
    QVERIFY(u1.getProfessions() == u2.getProfessions());
    QVERIFY(u1.getCurrentProfession() == u2.getCurrentProfession());
}

void iFacilityTest::test_db_add_user() {
    // 3 administrators (except u7), 1 dispatcher and 2 workers (for later)
    auto u1 = User::createUser("adm1", "test", UserType::ADMINISTRATOR, "f", "s", "t");
    auto u2 = User::createUser("adm2", "test", UserType::ADMINISTRATOR, "f", "s", "t");
    auto u3 = User::createUser("disp1", "test", UserType::DISPATCHER, "f", "s", "t");
    auto u4 = User::createUser("worker1", "test", UserType::WORKER, "f", "s", "t");
    auto u5 = User::createUser("worker2", "test", UserType::WORKER, "f", "s", "t");
    auto u6 = User::createUser("adm3", "test", UserType::ADMINISTRATOR, "f", "s", "t");
    auto u7 = User::createUser("adm1", "test", UserType::ADMINISTRATOR, "f", "s", "t");

    QVERIFY(Database::instance()->addUser(*u1));   // ok
    QVERIFY(Database::instance()->addUser(*u2));   // ok
    QVERIFY(Database::instance()->addUser(*u3));   // ok
    QVERIFY(Database::instance()->addUser(*u4));   // ok
    QVERIFY(Database::instance()->addUser(*u5));   // ok
    QVERIFY(Database::instance()->addUser(*u6));   // ok
    QVERIFY(!Database::instance()->addUser(*u7));  // u7 and u1 has same login

    sampleUser = *u1; // saved for later
}

void iFacilityTest::test_db_get_user_by_uid() {
    auto usr1 = Database::instance()->getUser(sampleUser.uID());
    UID nonExistentUuid = 0;
    auto usr2 = Database::instance()->getUser(nonExistentUuid);

    QVERIFY(usr1 != nullptr);
    QVERIFY(usr2 == nullptr);
}

void iFacilityTest::test_db_get_user_by_login() {
    auto usr1 = Database::instance()->getUser(sampleUser.getLogin());
    QString nonExistentLogin = "not_really_exists";
    auto usr2 = Database::instance()->getUser(nonExistentLogin);

    QVERIFY(usr1 != nullptr);
    QVERIFY(usr2 == nullptr);
}

void iFacilityTest::test_db_get_users_by_type() {
    auto admins = Database::instance()->getUsersByType(UserType::ADMINISTRATOR);
    auto dispatchers = Database::instance()->getUsersByType(UserType::DISPATCHER);
    auto workers = Database::instance()->getUsersByType(UserType::WORKER);

    QVERIFY(admins.size() == 3);
    QVERIFY(dispatchers.size() == 1);
    QVERIFY(workers.size() == 2);
}

void iFacilityTest::test_db_get_users_gy_profession() {
    auto usr1 = Database::instance()->getUser(sampleUser.getLogin());
    Profession p = Profession::createProfession("test_prof");
    usr1->addProfession(p.pID(), 3);

    QVERIFY(Database::instance()->addProfession(p));

    auto usrs = Database::instance()->getUsersByProfession(p.pID());

    QVERIFY(usrs.size() == 1);
    QVERIFY(usr1 == usrs[0]);

    sampleProfession = p;
}

void iFacilityTest::test_db_remove_dependant_profession() {
    QVERIFY(!Database::instance()->removeProfession(sampleProfession.pID()));
}

void iFacilityTest::test_db_remove_user() {
    QVERIFY(Database::instance()->removeUser(sampleUser.uID()));
    UID nonExistentUuid = 0;
    QVERIFY(!Database::instance()->removeUser(nonExistentUuid));
}

void iFacilityTest::test_db_remove_independant_profession() {
    QVERIFY(Database::instance()->removeProfession(sampleProfession.pID()));
    PID nonExistentPuid = 0;
    QVERIFY(!Database::instance()->removeProfession(nonExistentPuid));
}

QTEST_APPLESS_MAIN(iFacilityTest)

#include "tst_ifacilitytest.moc"
