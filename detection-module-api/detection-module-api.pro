#-------------------------------------------------
#
# Project created by QtCreator 2014-07-11T06:45:05
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = detection-module-api
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    DetectionModuleHolder.cpp \
    PluginLoader.cpp

HEADERS += \
    DetectionModuleHolder.h \
    DetectionModuleInterface.h \
    PluginLoader.h
