#-------------------------------------------------
#
# Project created by QtCreator 2016-05-17T16:54:17
#
#-------------------------------------------------

QT       -= gui

include(../global.pri)

TARGET = Brain
TEMPLATE = lib

DEFINES += BRAIN_LIBRARY

SOURCES += brain.cpp

HEADERS += brain.h\
        brain_global.h

DLLDESTDIR = $$OUT_PWD/../bin

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Backend/release/ -lBackend
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Backend/debug/ -lBackend

INCLUDEPATH += $$PWD/../Backend
DEPENDPATH += $$PWD/../Backend

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Logger/release/ -lLogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Logger/debug/ -lLogger
else:unix: LIBS += -L$$OUT_PWD/../Logger/ -lLogger

INCLUDEPATH += $$PWD/../Logger
DEPENDPATH += $$PWD/../Logger

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../common/debug/ -lcommon
else:unix: LIBS += -L$$OUT_PWD/../common/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
