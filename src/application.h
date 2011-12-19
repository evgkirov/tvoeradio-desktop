#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QDesktopServices>
#include <QDir>
#include <QIcon>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QNetworkProxy>
#include <QSettings>
#include "bridge.h"
#include "defines.h"
#include "networkcookiejar.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int & argc, char ** argv);
    ~Application();

    QNetworkAccessManager *networkAccessManager;
    Bridge *bridge;

    QMainWindow *mainWindow;

#ifdef Q_WS_MAC
    void setupMacHandlers();
#endif

signals:

public slots:

};


#endif // APPLICATION_H
