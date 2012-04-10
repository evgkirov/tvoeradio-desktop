#include <QCoreApplication>
#include "application.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName(APP_ORG);
    QCoreApplication::setOrganizationDomain(APP_DOMAIN);
    Application a(argc, argv);
    if (a.isRunning()) {
        return 0;
    }
    MainWindow w;    
    a.mainWindow = &w;
    a.setActivationWindow(&w);
    w.show();
    return a.exec();
}
