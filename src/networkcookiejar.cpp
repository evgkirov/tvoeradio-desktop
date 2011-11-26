#include "networkcookiejar.h"
#include <QDebug>
NetworkCookieJar::NetworkCookieJar(QString path, QObject *parent) :
    QNetworkCookieJar(parent)
{
    this->path = path;
    this->load();
}

NetworkCookieJar::~NetworkCookieJar()
{
    this->save();
}


void NetworkCookieJar::load()
{
    QFile file(this->path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString line;
    QList<QNetworkCookie> cookies;
    while (!file.atEnd()) {
        line = file.readLine();
        line.replace("\n", "");
        cookies.append(QNetworkCookie::parseCookies(line.toAscii()));
    }
    this->setAllCookies(cookies);
    file.close();
}

void NetworkCookieJar::save()
{
    QFile file(this->path);
    QList<QNetworkCookie> cookies = this->allCookies();
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QNetworkCookie cookie;
    for (int i = 0; i < cookies.count(); i++) {
        file.write(cookies[i].toRawForm() + "\n");
    }
    file.close();
}

void NetworkCookieJar::clear()
{
    QList<QNetworkCookie> cookies;
    this->setAllCookies(cookies);
    this->save();
}
