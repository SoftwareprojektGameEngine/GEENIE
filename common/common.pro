#-------------------------------------------------
#
# Project created by QtCreator 2016-05-02T15:06:41
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

include(../global.pri)

TARGET = common
TEMPLATE = lib

DEFINES += COMMON_LIBRARY

SOURCES += common.cpp

HEADERS += common.h\
        common_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
