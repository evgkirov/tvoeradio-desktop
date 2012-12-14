#include "application.h"

Application::Application(int & argc, char ** argv) :
    QtSingleApplication(argc, argv)
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
    connect(this->networkAccessManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(on_sslError(QNetworkReply*,QList<QSslError>)));

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
    this->bridge->networkCookieJar = (NetworkCookieJar*)this->networkAccessManager->cookieJar();

#ifdef Q_OS_LINUX
    this->mpris = new MPRIS(this);
#endif

#ifdef Q_WS_MAC
    this->setupMacHandlers();
#endif
}

Application::~Application()
{
    delete this->networkAccessManager;
}

void Application::on_sslError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    reply->ignoreSslErrors(errors);
}
