#ifndef BRIDGE_H
#define BRIDGE_H

#include <QApplication>
#include <QObject>
#include <QPalette>
#include <QVariantMap>

class Bridge : public QObject
{
    Q_OBJECT
public:
    explicit Bridge(QObject *parent = 0);

signals:
    void previous();
    void pause();
    void next();
    void playing_change(bool is_playing);
    void track_change(QString artist, QString title);

public slots:
    QString get_version();
    QVariantMap get_palette();

};

#endif // BRIDGE_H
