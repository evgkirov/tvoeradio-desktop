#include "application.h"

Application::Application(int & argc, char ** argv) :
    QApplication(argc, argv)
{
    QIcon icon;
    icon.addFile(":/icon");
    icon.addFile(":/icon16");
#ifndef Q_WS_MAC
    this->setWindowIcon(icon);
#endif
    this->setQuitOnLastWindowClosed(false);

    QString cachePath = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
    this->networkAccessManager = new QNetworkAccessManager();
    this->networkAccessManager->setCookieJar(new NetworkCookieJar(cachePath + "/cookies.txt", 0));
    QNetworkDiskCache* cache = new QNetworkDiskCache();
    cache->setCacheDirectory(cachePath);
    this->networkAccessManager->setCache(cache);

    QSettings settings;
    QNetworkProxy proxy;
    settings.beginGroup("Network");
    if (settings.value("Proxy", false).toBool()) {
        switch (settings.value("ProxyType", false).toInt()) {
        case 0: proxy.setType(QNetworkProxy::Socks5Proxy); break;
        case 1: proxy.setType(QNetworkProxy::HttpProxy); break;
        default: proxy.setType(QNetworkProxy::NoProxy); break;
        }
        proxy.setHostName(settings.value("ProxyHost").toString());
        proxy.setPort(settings.value("ProxyPort").toInt());
        proxy.setUser(settings.value("ProxyUser").toString());
        proxy.setPassword(settings.value("ProxyPassword").toString());
    } else {
        proxy.setType(QNetworkProxy::NoProxy);
    }
    settings.endGroup();
    QNetworkProxy::setApplicationProxy(proxy);

    this->bridge = new Bridge();
}

Application::~Application()
{
    delete this->networkAccessManager;
}




