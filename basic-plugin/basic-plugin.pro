#-------------------------------------------------
#
# Project created by QtCreator 2014-07-11T07:44:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = basic-plugin
TEMPLATE = lib

DEFINES += BASICPLUGIN_LIBRARY

include(basic-plugin.pri)

SOURCES += basicplugin.cpp

HEADERS += basicplugin.h\
        basic-plugin_global.h \
    DetectionModuleInterface.h \
    DetectionModuleHolder.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
