#-------------------------------------------------
#
# Project created by QtCreator 2016-04-28T14:22:01
#
#-------------------------------------------------

QT       += core gui opengl

include(../global.pri)

greaterThan(QT_MAJOR_VERSION, 4)

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
    scripthighlighter.cpp \
    assetwidget.cpp \
    inspector.cpp \
    exitdialog.cpp \
    sceneeditwidget.cpp \
    inspectorwidget.cpp \
    gdockwidget.cpp \
    sceneexplorer.cpp \
    inspectorparentwidget.cpp \
    inspectorpositionwidget.cpp \
    inspectorlightwidget.cpp \
    inspectormodelwidget.cpp \
    inspectormaterialwidget.cpp \
    inspectorshaderwidget.cpp \
    inspectortexturewidget.cpp \
    inspectorscriptcomponent.cpp \
    inspectorsoundwidget.cpp \
    addcomponentdialog.cpp \
    addentitydialog.cpp \
    renamescenedialog.cpp \
    renameentitydialog.cpp \
    newdialog.cpp \
    newprojectdialog.cpp \
    addscenedialog.cpp

HEADERS  += geeniemainwindow.h \
    geenie.h \
    ../tinyxml/tinystr.h \
    ../tinyxml/tinyxml.h \
    layoutform.h \
    scripthighlighter.h \
    assetwidget.h \
    inspector.h \
    exitdialog.h \
    sceneeditwidget.h \
    inspectorwidget.h \
    gdockwidget.h \
    sceneexplorer.h \
    inspectorparentwidget.h \
    inspectorpositionwidget.h \
    inspectorlightwidget.h \
    inspectormodelwidget.h \
    inspectormaterialwidget.h \
    inspectorshaderwidget.h \
    inspectortexturewidget.h \
    inspectorscriptcomponent.h \
    inspectorsoundwidget.h \
    addcomponentdialog.h \
    addentitydialog.h \
    renamescenedialog.h \
    renameentitydialog.h \
    newdialog.h \
    newprojectdialog.h \
    addscenedialog.h

FORMS    += geeniemainwindow.ui \
    layoutform.ui \
    assetwidget.ui \
    inspector.ui \
    exitdialog.ui \
    sceneeditwidget.ui \
    inspectorwidget.ui \
    sceneexplorer.ui \
    inspectorpositionwidget.ui \
    inspectorlightwidget.ui \
    inspectormodelwidget.ui \
    inspectormaterialwidget.ui \
    inspectorshaderwidget.ui \
    inspectortexturewidget.ui \
    inspectorscriptcomponent.ui \
    inspectorsoundwidget.ui \
    addcomponentdialog.ui \
    addentitydialog.ui \
    renamescenedialog.ui \
    renameentitydialog.ui \
    newdialog.ui \
    newprojectdialog.ui \
    addscenedialog.ui


win32: DESTDIR = $$OUT_PWD/../bin


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Logger/release/ -lLogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Logger/debug/ -lLogger

INCLUDEPATH += $$PWD/../Logger
DEPENDPATH += $$PWD/../Logger

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../common/debug/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GEENIE_Core/release/ -lGEENIE_Core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GEENIE_Core/debug/ -lGEENIE_Core

INCLUDEPATH += $$PWD/../GEENIE_Core
DEPENDPATH += $$PWD/../GEENIE_Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Backend/release/ -lBackend
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Backend/debug/ -lBackend

INCLUDEPATH += $$PWD/../Backend
DEPENDPATH += $$PWD/../Backend

RESOURCES += \
    images.qrc
