#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebView>
#include <webpage.h>
#include "application.h"

class WebView : public QWebView
{
    Q_OBJECT
public:
    WebView(QWidget *parent = 0);

protected:
    WebView* createWindow(QWebPage::WebWindowType type);

signals:

public slots:

};

#endif // WEBVIEW_H
