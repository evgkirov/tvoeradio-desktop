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
    networkcookiejar.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    webview.h \
    defines.h \
    webpage.h \
    application.h \
    bridge.h \
    networkcookiejar.h \
    settingsdialog.h

FORMS += \
    settingsdialog.ui

RESOURCES += \
    tvoeradio-desktop.qrc

OTHER_FILES += \
    tvoeradio-desktop.rc

RC_FILE = tvoeradio-desktop.rc

exists(/usr/include/qxt) { # Ubuntu WTF, part 1
    INCLUDEPATH += /usr/include/qxt /usr/include/qxt/QxtCore /usr/include/qxt/QxtGui
}

exists(/usr/lib/libQxtGui.so.0) { # Ubuntu WTF, part 2
    LIBS += /usr/lib/libQxtCore.so.0 /usr/lib/libQxtGui.so.0
}

unix {
    target.path = /usr/bin/
    images.path = /usr/share/pixmaps
    images.files += img/tvoeradio-desktop.png
    desktop.path = /usr/share/applications
    desktop.files += tvoeradio-desktop.desktop
    INSTALLS += target \
        images \
        desktop
}
