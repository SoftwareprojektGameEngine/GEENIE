<<<<<<< HEAD
#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T10:25:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GEENIE
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32 {
    CONFIG(release, debug|release):LIBS += -L$$PWD/lib -losgDB -losgViewer -losgQt
    CONFIG(debug, debug|release):LIBS += -L$$PWD/lib -losgDBd -losgViewerd -losgQtd
}

INCLUDEPATH += $$PWD/osg-include
DEPENDPATH += $$PWD/osg-include
=======
TEMPLATE = subdirs

SUBDIRS += \
    GEENIE \
    Logger

GEENIE.depends = Logger
>>>>>>> 9b35ea7ad01253c979ea64a27b51d19c1556ff2a
