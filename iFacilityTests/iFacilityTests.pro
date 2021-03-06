QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_ifacilitytest.cpp \
            ..\iFacility\objects\userprofession.cpp \
            ..\iFacility\objects\profession.cpp \
            ..\iFacility\objects\user.cpp \
            ..\iFacility\db\database.cpp

HEADERS +=  ..\iFacility\objects\userprofession.h \
            ..\iFacility\objects\profession.h \
            ..\iFacility\objects\user.h \
            ..\iFacility\db\database.h
