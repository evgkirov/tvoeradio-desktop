#include "application.h"

Application::Application(int & argc, char ** argv) :
    QApplication(argc, argv)
{
    QIcon icon;
    icon.addFile(":/icon");
    icon.addFile(":/icon16");
    this->setWindowIcon(icon);
    this->setQuitOnLastWindowClosed(false);

    QString cachePath = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
    this->networkAccessManager = new QNetworkAccessManager();
    this->networkAccessManager->setCookieJar(new NetworkCookieJar(cachePath + "/cookies.txt", 0));
    QNetworkDiskCache* cache = new QNetworkDiskCache();
    cache->setCacheDirectory(cachePath);
    this->networkAccessManager->setCache(cache);

    this->bridge = new Bridge();

}

Application::~Application()
{
    delete this->networkAccessManager;
}




