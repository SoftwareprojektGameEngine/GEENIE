#-------------------------------------------------
#
# Project created by QtCreator 2016-05-17T16:55:33
#
#-------------------------------------------------

QT       -= gui

include(../global.pri)

TARGET = Backend
TEMPLATE = lib

DEFINES += BACKEND_LIBRARY

SOURCES += \
    osgwrapper.cpp

HEADERS +=\
        backend_global.h \
    osgwrapper.h

DLLDESTDIR = $$OUT_PWD/../bin

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GEENIE_Core/release/ -lGEENIE_Core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GEENIE_Core/debug/ -lGEENIE_Core
else:unix: LIBS += -L$$OUT_PWD/../GEENIE_Core/ -lGEENIE_Core

INCLUDEPATH += $$PWD/../GEENIE_Core
DEPENDPATH += $$PWD/../GEENIE_Core

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OpenScenegraph/lib/ -losg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OpenScenegraph/lib/ -losgd
else:unix: LIBS += -L$$PWD/../OpenScenegraph/lib/ -losg

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OpenScenegraph/lib/ -losgDB
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OpenScenegraph/lib/ -losgDBd
else:unix: LIBS += -L$$PWD/../OpenScenegraph/lib/ -losgDB

INCLUDEPATH += $$PWD/../OpenScenegraph/include
DEPENDPATH += $$PWD/../OpenScenegraph/include
