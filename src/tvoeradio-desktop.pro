#-------------------------------------------------
#
# Project created by QtCreator 2011-11-19T14:33:13
#
#-------------------------------------------------

QT       += core gui network webkit
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

# Qxt
!macx:SOURCES += qxtglobalshortcut.cpp
!macx:HEADERS += qxtglobalshortcut_p.h \
    qxtglobalshortcut.h \
    qxtglobal.h
win32:SOURCES += qxtglobalshortcut_win.cpp
unix:!macx:SOURCES += qxtglobalshortcut_x11.cpp

# Mac OS
macx:OBJECTIVE_SOURCES += application_mac.mm
macx:LIBS += -framework Cocoa
macx: QMAKE_INFO_PLIST = mac/Info.plist
macx:localizations.files = mac/ru.lproj/InfoPlist.strings
macx:localizations.path = Contents/Resources/ru.lproj
macx:QMAKE_BUNDLE_DATA += localizations

FORMS += \
    settingsdialog.ui

RESOURCES += \
    tvoeradio-desktop.qrc

OTHER_FILES += \
    tvoeradio-desktop.rc

RC_FILE = tvoeradio-desktop.rc


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


# [arch] error: qxtglobalshortcut_x11.o: undefined reference to symbol 'XSync'
exists(/usr/lib/libX11.so.6) {
    LIBS += /usr/lib/libX11.so.6
}
