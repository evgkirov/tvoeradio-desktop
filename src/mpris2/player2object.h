/***************************************************************************
 *   Copyright (C) 2010 by Ilya Kotov                                      *
 *   forkotov02@hotmail.ru                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/
#ifndef PLAYER2OBJECT_H
#define PLAYER2OBJECT_H

#include <QDBusAbstractAdaptor>
#include <QVariantMap>
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
class Player2Object : public QDBusAbstractAdaptor
{
Q_OBJECT
Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")
Q_PROPERTY(bool CanControl READ canControl)
Q_PROPERTY(bool CanGoNext READ canGoNext)
Q_PROPERTY(bool CanGoPrevious READ canGoPrevious)
Q_PROPERTY(bool CanPause READ canPause)
Q_PROPERTY(bool CanPlay READ canPlay)
Q_PROPERTY(bool CanSeek READ canSeek)
Q_PROPERTY(double MaximumRate READ maximumRate)
Q_PROPERTY(QVariantMap Metadata READ metadata)
Q_PROPERTY(double MinimumRate READ minimumRate)
Q_PROPERTY(QString PlaybackStatus READ playbackStatus)
Q_PROPERTY(qlonglong Position READ position)
Q_PROPERTY(double Rate READ rate WRITE setRate)
Q_PROPERTY(double Volume READ volume WRITE setVolume)
public:
    Player2Object(QObject *parent = 0);
    virtual ~Player2Object();
    bool canControl() const;
    bool canGoNext() const;
    bool canGoPrevious() const;
    bool canPause() const;
    bool canPlay() const;
    bool canSeek() const;
    double maximumRate() const;
    QVariantMap metadata() const;
    double minimumRate() const;
    QString playbackStatus() const;
    qlonglong position() const;
    double rate() const;
    void setRate(double value);
    double volume() const;
    void setVolume(double value);

public slots:
    void Next();
    void Pause();
    void Play();
    void PlayPause();
    void Previous();
    void Stop();
    void Seek(qlonglong Offset);
    void SetPosition(const QDBusObjectPath&, qlonglong);
    void SongChanged(QString artist , QString title);
    void SetPlayState(bool);
    void updateId();


signals:
    void Seeked(qlonglong Position);
    void PropertiesChanged(QVariantList);
private slots:
    void emitPropertiesChanged();

private:
    Bridge *bridge;
    void syncProperties();
    QMap<QString, QVariant> m_props;
    QDBusObjectPath m_trackID;
    bool playstate;
    bool playstarted;
    QString artist, title, prevart, prevtitle;
signals:
    void next();
    void previous();
    void pause();
    void playingchanged(bool);

};

#endif
