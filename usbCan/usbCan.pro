#-------------------------------------------------
#
# Project created by QtCreator 2017-08-17T19:54:20
#
#-------------------------------------------------

QT += core gui
QT += widgets

TARGET = usbCan
TEMPLATE = app

win32 {
    DEFINES += _WINDOWS
    msvc {
        LIBS += ./lib/zcoma.lib
    }
    else {
        DEFINES += WIN32MINGW
        LIBS += ./lib/zcoma.lib
    }

}

unix {
    DEFINES += _LINUX
}

debug {
    DEFINES +=
}

INCLUDEPATH += ./utils ./service

SOURCES += main.cpp\
        widget.cpp \
    service/Service.cpp

HEADERS  += widget.h \
    utils/zcoma.h \
    utils/initDefine.h \
    service/Service.h
