#-------------------------------------------------
#
# Project created by QtCreator 2017-08-17T19:54:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = usbCan
TEMPLATE = app

win32 {
    msvc {
        LIBS += ./lib/zcoma.lib
    }
    else {
        DEFINES += WIN32MINGW
    }

}

unix {

}

DEFINES += _LINUX
#LIBS += -L./lib -lzcoma

INCLUDEPATH += ./utils

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    utils/zcoma.h \
    utils/initDefine.h
