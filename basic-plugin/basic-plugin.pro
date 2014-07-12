#-------------------------------------------------
#
# Project created by QtCreator 2014-07-11T07:44:26
#
#-------------------------------------------------

QT       -= gui

TARGET = basic-plugin
TEMPLATE = lib

DEFINES += BASICPLUGIN_LIBRARY

SOURCES += basicplugin.cpp

HEADERS += basicplugin.h\
        basic-plugin_global.h \
    DetectionModuleInterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
