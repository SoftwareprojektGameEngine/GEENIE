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
        geeniemainwindow.cpp

HEADERS  += geeniemainwindow.h

FORMS    += geeniemainwindow.ui


win32: DESTDIR = $$OUT_PWD/../bin
