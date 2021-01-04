#include <QApplication>
#include "loginwindow.h"

#include "db/database.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Database::instance()->load();

    LoginWindow w;
    w.show();

    QObject::connect(&a, &QApplication::aboutToQuit, []() {
        Database::instance()->save();
    });
    return a.exec();
}
