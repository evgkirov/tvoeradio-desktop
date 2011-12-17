#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QDesktopServices>
#include <QWebFrame>
#include <QWebSettings>
#include <QWebPage>
#include "application.h"

class WebPage : public QWebPage
{
    Q_OBJECT
public:
    explicit WebPage(QObject *parent = 0);

protected:
    QString userAgentForUrl(const QUrl &url) const;

signals:

public slots:
    void on_windowCloseRequested();
    void on_linkClicked(QUrl url);
    void on_javaScriptWindowObjectCleared();

};

#endif // WEBPAGE_H
