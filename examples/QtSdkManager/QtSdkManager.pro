#-------------------------------------------------
#
# Project created by QtCreator 2017-10-08T23:30:20
#
#-------------------------------------------------
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#QQt source root on your computer
equals(QMAKE_HOST.os, Darwin) {
    QQT_SOURCE_ROOT = /Users/abel/Develop/a0-develop/a0-qqtfoundation
} else: equals(QMAKE_HOST.os, Linux) {
    QQT_SOURCE_ROOT = /home/abel/Develop/a0-develop/LibQt
} else: equals(QMAKE_HOST.os, Windows) {
    QQT_SOURCE_ROOT = C:/Users/Administrator/Develop/a0-develop/a0-qqtfoundation
}

include($${QQT_SOURCE_ROOT}/src/qqt_version.pri)
include($${QQT_SOURCE_ROOT}/src/qqt_header.pri)
#CONFIG += BUILD_SRC
contains (CONFIG, BUILD_SRC) {
    #if you want to build src but not link QQt in this project
    include($${QQT_SOURCE_ROOT}/src/qqt_source.pri)
} else {
    #if you want to link QQt library
    include($${QQT_SOURCE_ROOT}/src/qqt_library.pri)
}


QT += core gui network sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += __QT5__

#this name must be equals to pro name
TARGET = QtSdkManager
TEMPLATE = app

INCLUDEPATH +=  $$PWD

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
