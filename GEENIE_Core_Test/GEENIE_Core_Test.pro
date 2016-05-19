#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T16:28:24
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

include(../global.pri)

TARGET = project_test
CONFIG   += console testcase
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = $$OUT_PWD/../bin
SOURCES += \
    project_test.cpp \
    main.cpp \
    entity_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GEENIE_Core/release/ -lGEENIE_Core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GEENIE_Core/debug/ -lGEENIE_Core
else:unix: LIBS += -L$$OUT_PWD/../GEENIE_Core/ -lGEENIE_Core

INCLUDEPATH += $$PWD/../GEENIE_Core
DEPENDPATH += $$PWD/../GEENIE_Core

HEADERS += \
    project_test.h \
    entity_test.h
