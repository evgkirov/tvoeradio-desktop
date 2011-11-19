#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QDesktopServices>
#include <QDir>
#include <QIcon>
#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
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

signals:

public slots:

};


#endif // APPLICATION_H
