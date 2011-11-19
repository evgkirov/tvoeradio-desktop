#ifndef NETWORKCOOKIEJAR_H
#define NETWORKCOOKIEJAR_H

#include <QFile>
#include <QIODevice>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QObject>

class NetworkCookieJar : public QNetworkCookieJar
{
    Q_OBJECT
public:
    explicit NetworkCookieJar(QString path, QObject *parent = 0);
    ~NetworkCookieJar();
    void save();
    void load();

    QString path;

signals:

public slots:

};

#endif // NETWORKCOOKIEJAR_H
