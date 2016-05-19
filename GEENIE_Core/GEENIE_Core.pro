#-------------------------------------------------
#
# Project created by QtCreator 2016-05-17T15:58:11
#
#-------------------------------------------------

QT       -= gui

include(../global.pri)

TARGET = GEENIE_Core
TEMPLATE = lib

DEFINES += GEENIE_CORE_LIBRARY

DLLDESTDIR = $$OUT_PWD/../bin

SOURCES += \
    project.cpp \
    scriptasset.cpp \
    textureasset.cpp \
    modelasset.cpp \
    materialasset.cpp \
    entity.cpp \
    createentityaction.cpp \
    removeentityaction.cpp \
    addcomponentaction.cpp \
    modifyentityaction.cpp \
    scene.cpp \
    addsceneaction.cpp \
    addassetaction.cpp \
    removesceneaction.cpp \
    removeassetaction.cpp

HEADERS +=\
        geenie_core_global.h \
    useractions.h \
    core.h \
    assets.h \
    components.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#QMAKE_LFLAGS += /NoEntry
