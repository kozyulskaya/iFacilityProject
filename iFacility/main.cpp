#include <QApplication>
#include "loginwindow.h"

#include "db/database.h"

/**
 * @brief Основная точка входа в приложение
 * 
 * @param argc Кол-во аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return int Код выхода приложения
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //! Считываем данные в систему
    Database::instance()->load();

    //! Открываем окно авторизации
    LoginWindow w;
    w.show();

    //! Подписываемся на событие закрытия приложения, для сохранения данных на диск
    QObject::connect(&a, &QApplication::aboutToQuit, []() {
        Database::instance()->save();
    });
    return a.exec();
}
