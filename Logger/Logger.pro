#-------------------------------------------------
#
# Project created by QtCreator 2016-04-28T14:29:28
#
#-------------------------------------------------

QT       += widgets

include(../global.pri)

TARGET = Logger
TEMPLATE = lib

DEFINES += LOGGER_LIBRARY

SOURCES += logger.cpp \
    loggerwidget.cpp \
    loggerlistmodel.cpp \
    loggerlistitem.cpp \
    loggerfiltermodel.cpp

HEADERS += logger.h\
        logger_global.h \
    loggerwidget.h \
    loggerlistmodel.h \
    loggerlistitem.h \
    loggerfiltermodel.h

DLLDESTDIR = $$OUT_PWD/../bin

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    loggerwidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../common/debug/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
