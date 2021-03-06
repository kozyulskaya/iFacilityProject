QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    administrationpanel.cpp \
    main.cpp \
    loginwindow.cpp \
    objects/profession.cpp \
    objects/user.cpp \
    objects/userprofession.cpp \
    db/database.cpp \
    registrationdialog.cpp \
    viewmodels/administrationviewmodel.cpp \
    viewmodels/professionsviewmodel.cpp \
    viewmodels/userprofessionviewmodel.cpp \
    viewmodels/workersviewmodel.cpp \
    workerpanel.cpp

HEADERS += \
    administrationpanel.h \
    loginwindow.h \
    objects/profession.h \
    objects/user.h \
    objects/userprofession.h \
    db/database.h \
    registrationdialog.h \
    viewmodels/administrationviewmodel.h \
    viewmodels/professionsviewmodel.h \
    viewmodels/userprofessionviewmodel.h \
    viewmodels/workersviewmodel.h \
    workerpanel.h

FORMS += \
    administrationpanel.ui \
    loginwindow.ui \
    registrationdialog.ui \
    workerpanel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
