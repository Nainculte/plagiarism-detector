#-------------------------------------------------
#
# Project created by QtCreator 2014-06-30T15:28:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Plagiarism-Detector
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sourcemodel.cpp \
    modulemodel.cpp \
    managemoduledialog.cpp \
    managesourcesdialog.cpp

HEADERS  += mainwindow.h \
    sourcemodel.h \
    modulemodel.h \
    managemoduledialog.h \
    managesourcesdialog.h \
    DetectionModuleHolder.h \
    DetectionModuleInterface.h

FORMS    +=

OTHER_FILES +=

RESOURCES += \
    resouces.qrc
