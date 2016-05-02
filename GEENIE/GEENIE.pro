#-------------------------------------------------
#
# Project created by QtCreator 2016-04-28T14:22:01
#
#-------------------------------------------------

QT       += core gui

include(../global.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GEENIE
TEMPLATE = app


SOURCES += main.cpp\
        geeniemainwindow.cpp \
    geenie.cpp

HEADERS  += geeniemainwindow.h \
    geenie.h

FORMS    += geeniemainwindow.ui


win32: DESTDIR = $$OUT_PWD/../bin


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Logger/release/ -lLogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Logger/debug/ -lLogger

INCLUDEPATH += $$PWD/../Logger
DEPENDPATH += $$PWD/../Logger

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../common/debug/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
