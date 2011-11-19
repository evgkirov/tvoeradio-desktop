#include "webview.h"

WebView::WebView(QWidget *parent)
    : QWebView(parent)
{
    this->setPage(new WebPage(this));
}

WebView* WebView::createWindow(QWebPage::WebWindowType type)
{
    Q_UNUSED(type);
    WebView* loginView = new WebView(this->parentWidget());
    loginView->resize(this->parentWidget()->size());
    loginView->show();
    return loginView;
}
