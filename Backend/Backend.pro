#-------------------------------------------------
#
# Project created by QtCreator 2016-05-17T16:55:33
#
#-------------------------------------------------

QT += opengl

include(../global.pri)

TARGET = Backend
TEMPLATE = lib

DEFINES += BACKEND_LIBRARY

SOURCES += \
    osgwrapper.cpp \
    osgwidget.cpp \
    viewerex.cpp \
    cullvisitorex.cpp \
    graphicswindowex.cpp \
    renderstagecacheex.cpp \
    renderstageex.cpp \
    stateex.cpp \
    compositeviewerex.cpp

HEADERS +=\
        backend_global.h \
    osgwrapper.h \
    osgwidget.h \
    viewerex.h \
    renderstagecacheex.h \
    stateex.h \
    renderstageex.h \
    cullvisitorex.h \
    graphicswindowex.h \
    compositeviewerex.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OpenScenegraph/lib/ -losg -losgDB -losgGA -losgViewer -losgUtil -lOpenThreads -lglut32 -lopengl32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OpenScenegraph/lib/ -losgd -losgDBd -losgGAd -losgViewerd -losgUtild -lOpenThreadsd -lglut32d -lopengl32
else:unix: LIBS += -L$$PWD/../OpenScenegraph/lib/ -losg -losgDB -losgGA -losgViewer -losgUtil -lOpenThreads -lglut32 -lopengl32

INCLUDEPATH += $$PWD/../OpenScenegraph/include
DEPENDPATH += $$PWD/../OpenScenegraph/include
