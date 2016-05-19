#-------------------------------------------------
#
# Project created by QtCreator 2016-04-28T14:22:01
#
#-------------------------------------------------

QT       += core gui opengl

include(../global.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GEENIE
TEMPLATE = app


SOURCES += main.cpp\
        geeniemainwindow.cpp \
    geenie.cpp \
    ../tinyxml/tinystr.cpp \
    ../tinyxml/tinyxml.cpp \
    ../tinyxml/tinyxmlerror.cpp \
    ../tinyxml/tinyxmlparser.cpp \
    layoutform.cpp \
    newprojectwidget.cpp \
    scripthighlighter.cpp

HEADERS  += geeniemainwindow.h \
    geenie.h \
    ../tinyxml/tinystr.h \
    ../tinyxml/tinyxml.h \
    layoutform.h \
    newprojectwidget.h \
    scripthighlighter.h

FORMS    += geeniemainwindow.ui \
    layoutform.ui \
    newprojectwidget.ui


win32: DESTDIR = $$OUT_PWD/../bin


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Logger/release/ -lLogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Logger/debug/ -lLogger

INCLUDEPATH += $$PWD/../Logger
DEPENDPATH += $$PWD/../Logger

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../common/debug/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Brain/release/ -lBrain
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Brain/debug/ -lBrain

INCLUDEPATH += $$PWD/../Brain
DEPENDPATH += $$PWD/../Brain

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Backend/release/ -lBackend
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Backend/debug/ -lBackend

INCLUDEPATH += $$PWD/../Backend
DEPENDPATH += $$PWD/../Backend
