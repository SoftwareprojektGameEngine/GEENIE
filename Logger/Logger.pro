#-------------------------------------------------
#
# Project created by QtCreator 2016-04-28T14:29:28
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

include(../global.pri)

TARGET = Logger
TEMPLATE = lib

DEFINES += LOGGER_LIBRARY

SOURCES += logger.cpp

HEADERS += logger.h\
        logger_global.h

DLLDESTDIR = $$OUT_PWD/../bin

unix {
    target.path = /usr/lib
    INSTALLS += target
}
