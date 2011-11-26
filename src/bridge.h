#ifndef BRIDGE_H
#define BRIDGE_H

#include <QApplication>
#include <QObject>
#include <QPalette>
#include <QVariantMap>
#include "networkcookiejar.h"

class Bridge : public QObject
{
    Q_OBJECT
public:
    explicit Bridge(QObject *parent = 0);
    NetworkCookieJar *networkCookieJar;

signals:
    void previous();
    void pause();
    void next();
    void playing_change(bool is_playing);
    void track_change(QString artist, QString title);

public slots:
    QString get_version();
    QVariantMap get_palette();
    void logout();

};

#endif // BRIDGE_H
