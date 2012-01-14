#include "webpage.h"

WebPage::WebPage(QObject *parent) :
    QWebPage(parent)
{
    QString cachePath = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
    connect(this, SIGNAL(windowCloseRequested()), this, SLOT(on_windowCloseRequested()));
    connect(this, SIGNAL(linkClicked(QUrl)), this, SLOT(on_linkClicked(QUrl)));
    connect(this->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(on_javaScriptWindowObjectCleared()));
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(on_loadFinished(bool)));
    this->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    this->setNetworkAccessManager(qApp->networkAccessManager);
    this->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    this->settings()->setAttribute(QWebSettings::JavaEnabled, false);
    this->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    this->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    this->settings()->setLocalStoragePath(cachePath);
}

QString WebPage::userAgentForUrl(const QUrl &url) const
{
    // Убираем "Safari/533.3" из конца строки user agent
    QString ua = QWebPage::userAgentForUrl(url);
    int last_space = ua.lastIndexOf(' ');
    return ua.left(last_space);
}

void WebPage::on_windowCloseRequested()
{
    ((QWidget*)this->parent())->close();
}

void WebPage::on_linkClicked(QUrl url)
{
    QDesktopServices::openUrl(url);
}

void WebPage::on_javaScriptWindowObjectCleared()
{
    this->mainFrame()->addToJavaScriptWindowObject("bridge", qApp->bridge);
}

void WebPage::on_loadFinished(bool ok)
{
    ((NetworkCookieJar*)qApp->networkAccessManager->cookieJar())->save();
}
