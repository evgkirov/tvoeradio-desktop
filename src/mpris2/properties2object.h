#ifndef PROPERTIES2OBJECT_H
#define PROPERTIES2OBJECT_H

#include <QDBusAbstractAdaptor>
#include <QVariantList>
#include <QDBusObjectPath>
#include <QMap>
#include <QUuid>
#include <QDBusObjectPath>
#include <bridge.h>
#include <QDBusMessage>


/**
    @author Ilya Kotov <forkotov02@hotmail.ru>
    @author Konstantin Mescheryakov <m.keyran@gmail.com>
*/
class Properties2Object : public QDBusAbstractAdaptor
{
Q_OBJECT
Q_CLASSINFO("D-Bus Interface", "org.freedesktop.DBus.Properties")

public:
    Properties2Object(QObject *parent = 0);
    virtual ~Properties2Object();

public slots:

signals:
    void PropertiesChanged(QVariantList);
};

#endif // PROPERTIES2OBJECT_H
