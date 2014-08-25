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
    managesourcesdialog.cpp \
    quitdialog.cpp \
    resultmodel.cpp \
    treenode.cpp \
    moduleresultwrapper.cpp \
    analysisresult.cpp \
    summarymodule.cpp \
    resultfilterproxymodel.cpp

HEADERS  += mainwindow.h \
    sourcemodel.h \
    modulemodel.h \
    managemoduledialog.h \
    managesourcesdialog.h \
    DetectionModuleHolder.h \
    DetectionModuleInterface.h \
    quitdialog.h \
    resultmodel.h \
    treenode.h \
    moduleresultwrapper.h \
    analysisresult.h \
    summarymodule.h \
    resultfilterproxymodel.h

FORMS    +=

OTHER_FILES +=

RESOURCES += \
    resouces.qrc
