#include "webpage.h"

WebPage::WebPage(QObject *parent) :
    QWebPage(parent)
{
    connect(this, SIGNAL(windowCloseRequested()), this, SLOT(on_windowCloseRequested()));
    connect(this, SIGNAL(linkClicked(QUrl)), this, SLOT(on_linkClicked(QUrl)));
    connect(this->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(on_javaScriptWindowObjectCleared()));
    this->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    this->setNetworkAccessManager(qApp->networkAccessManager);
    this->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    this->settings()->setAttribute(QWebSettings::JavaEnabled, false);
    this->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    this->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
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
