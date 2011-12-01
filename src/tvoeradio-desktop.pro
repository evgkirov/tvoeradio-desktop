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
    settingsdialog.cpp \
    qxtglobalshortcut.cpp

HEADERS  += mainwindow.h \
    webview.h \
    defines.h \
    webpage.h \
    application.h \
    bridge.h \
    networkcookiejar.h \
    settingsdialog.h \
    qxtglobalshortcut_p.h \
    qxtglobalshortcut.h \
    qxtglobal.h

macx:SOURCES += qxtglobalshortcut_mac.cpp
win32:SOURCES += qxtglobalshortcut_win.cpp
unix:!macx:SOURCES += qxtglobalshortcut_x11.cpp

FORMS += \
    settingsdialog.ui

RESOURCES += \
    tvoeradio-desktop.qrc

OTHER_FILES += \
    tvoeradio-desktop.rc

RC_FILE = tvoeradio-desktop.rc

QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.6.sdk
ICON = img/tvoeradio-desktop.icns

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
