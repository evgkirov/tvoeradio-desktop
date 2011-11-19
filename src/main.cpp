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
    MainWindow w;
    w.show();
    return a.exec();
}
