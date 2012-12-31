/***********************************************************************
 * Copyright 2010  Canonical Ltd
 *   (author: Aurelien Gateau <aurelien.gateau@canonical.com>)
 * Copyright 2012  Eike Hein <hein@kde.org>
 * Copyright 2012  Alex Merry <alex.merry@kdemail.net>
 * Copyright 2013  Konstantin Mescheryakov <m.keyran@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#include "MediaPlayer2Player.h"

#include <QCryptographicHash>
#include "application.h"

static QDBusObjectPath mprisTrackId(QString artist, QString title) {
    QString path;
    QString p;
    for (int i = 0; i < artist.length(); i++) {
        if (artist[i].isLetter()) p.append(artist[i]);
    }
    for (int i = 0; i < title.length(); i++) {
        if (title[i].isLetter()) p.append(title[i]);
    }
    path = (QString("%1/Track/%2").arg("/org/mpris/MediaPlayer2").arg(p));
    return QDBusObjectPath( path );
}


MediaPlayer2Player::MediaPlayer2Player(QObject *parent)
    : DBusAbstractAdaptor(parent) {
    bridge = qApp->bridge;
    playstarted = false;
    playstate = false;
    connect(bridge, SIGNAL(track_change(QString, QString)), this, SLOT(trackChanged(QString, QString)));
    connect(bridge, SIGNAL(playing_change(bool)), this, SLOT(playbackStateChanged(bool)));
}

MediaPlayer2Player::~MediaPlayer2Player() {
}

bool MediaPlayer2Player::CanGoNext() const {
    if (playstarted) return true;
    return false;
}

void MediaPlayer2Player::Next() {
    playstate = true;
    QMetaObject::invokeMethod(bridge, "next");
}

bool MediaPlayer2Player::CanGoPrevious() const {
    if (playstarted) return true;
    return false;
}

void MediaPlayer2Player::Previous() {
    playstate = true;
    QMetaObject::invokeMethod(bridge, "previous");
}

bool MediaPlayer2Player::CanPause() const {
    if (playstarted) return true;
    return false;
}

void MediaPlayer2Player::Pause() {
    if (playstate)
        QMetaObject::invokeMethod(bridge, "pause");
}

void MediaPlayer2Player::PlayPause() {
    QMetaObject::invokeMethod(bridge, "pause");
}

void MediaPlayer2Player::Stop() {
    if (playstate)
        QMetaObject::invokeMethod(bridge, "pause");
}

bool MediaPlayer2Player::CanPlay() const {
    return true;
}

void MediaPlayer2Player::Play() {
    if (!playstate)
        QMetaObject::invokeMethod(bridge, "pause");
}

void MediaPlayer2Player::SetPosition( const QDBusObjectPath &TrackId, qlonglong position ) const {
    Q_UNUSED(TrackId)
    Q_UNUSED(position)
}


QString MediaPlayer2Player::PlaybackStatus() const {
    if ( playstate )
        return QLatin1String( "Playing" );
    else if ( playstarted && !playstate )
        return QLatin1String( "Paused" );
    else
        return QLatin1String( "Stopped" );
}

QString MediaPlayer2Player::LoopStatus() const {
    return QLatin1String( "None" );
}

void MediaPlayer2Player::setLoopStatus( const QString &status ) const {
    Q_UNUSED(status)
}

double MediaPlayer2Player::Rate() const {
    return 1.0;
}

void MediaPlayer2Player::setRate( double rate ) const {
    Q_UNUSED(rate)
}

bool MediaPlayer2Player::Shuffle() const {
    return true;
}

void MediaPlayer2Player::setShuffle( bool shuffle ) const {
    Q_UNUSED(shuffle)
}

QVariantMap MediaPlayer2Player::metadataForTrack( QString artist, QString title ) const {
    QVariantMap map;
    if (!artist.isEmpty())
        map["xesam:artist"] = QStringList() << artist;
    if (!title.isEmpty())
        map["xesam:title"] =  title;
    map["mpris:trackid"] = m_trackID.path();
    return map;
}

QVariantMap MediaPlayer2Player::Metadata() const {
    return metadataForTrack( this->artist, this->title );
}

double MediaPlayer2Player::Volume() const {
    return 1;
}

void MediaPlayer2Player::setVolume( double volume ) const {
    Q_UNUSED(volume)
}

qlonglong MediaPlayer2Player::Position() const {
    return 0;
}

double MediaPlayer2Player::MinimumRate() const {
    return 1.0;
}

double MediaPlayer2Player::MaximumRate() const {
    return 1.0;
}

bool MediaPlayer2Player::CanSeek() const {
    return false;
}

void MediaPlayer2Player::Seek( qlonglong Offset ) const {
    Q_UNUSED(Offset)
}

bool MediaPlayer2Player::CanControl() const {
    return true;
}

void MediaPlayer2Player::trackPositionChanged( qint64 position, bool userSeek ) {
    Q_UNUSED(position)
    Q_UNUSED(userSeek)
}

void MediaPlayer2Player::trackChanged( QString artist, QString title ) {
    m_trackID = mprisTrackId(artist, title);
    this->artist = artist;
    this->title = title;
    signalPropertyChange( "CanPause", CanPause() );
    signalPropertyChange( "Metadata", metadataForTrack( artist, title) );
}



void MediaPlayer2Player::seekableChanged( bool seekable ) {
    signalPropertyChange( "CanSeek", seekable );
}

void MediaPlayer2Player::volumeChanged( int percent ) {
    Q_UNUSED(percent)
}

void MediaPlayer2Player::trackLengthChanged( qint64 milliseconds ) {
    Q_UNUSED( milliseconds )
    signalPropertyChange( "Metadata", Metadata() );
}

void MediaPlayer2Player::playbackStateChanged(bool is_playing) {
    if (is_playing) {
        playstarted = true;
        playstate = true;
    } else {
        playstate = false;
    }
    signalPropertyChange( "PlaybackStatus", PlaybackStatus() );
}
