#-------------------------------------------------
#
# Project created by QtCreator 2011-11-19T14:33:13
#
#-------------------------------------------------

QT       += core gui network webkit
CONFIG   += qxt
QXT      += core gui
TARGET = tvoeradio-desktop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webview.cpp \
    webpage.cpp \
    application.cpp \
    bridge.cpp \
    networkcookiejar.cpp

HEADERS  += mainwindow.h \
    webview.h \
    defines.h \
    webpage.h \
    application.h \
    bridge.h \
    networkcookiejar.h

RESOURCES += \
    tvoeradio.qrc

exists(/usr/include/qxt) { # Ubuntu WTF
    INCLUDEPATH += /usr/include/qxt /usr/include/qxt/QxtCore /usr/include/qxt/QxtGui
    LIBS += /usr/lib/libQxtGui.so.0 /usr/lib/libQxtGui.so.0
}
