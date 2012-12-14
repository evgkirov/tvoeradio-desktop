/***************************************************************************
 *   Copyright (C) 2010-2012 by Ilya Kotov                                 *
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

#include <QFile>
#include <QDBusMetaType>
#include <QDBusArgument>
#include <QDBusConnection>
#include "player2object.h"
#include <application.h>

Player2Object::Player2Object(QObject *parent) : QDBusAbstractAdaptor(parent) {
    bridge = qApp->bridge;
    playstarted = true;
    connect (bridge, SIGNAL(track_change(QString, QString)), SLOT(emitPropertiesChanged()));
    connect (bridge, SIGNAL(track_change(QString, QString)), SLOT(updateId()));
    connect (bridge, SIGNAL(track_change(QString, QString)), SLOT(SongChanged(QString, QString)));
    connect (bridge, SIGNAL(playing_change(bool)), SLOT(emitPropertiesChanged()));
    connect (bridge, SIGNAL(playing_change(bool)), SLOT(SetPlayState(bool)));
    connect (this, SIGNAL(next()), bridge, SIGNAL(next()));
    connect (this, SIGNAL(previous()), bridge, SIGNAL(previous()));
    connect (this, SIGNAL(pause()), bridge, SIGNAL(pause()));
    connect (this, SIGNAL(playingchanged(bool)), bridge, SIGNAL(playing_change(bool)));
    connect (this, SIGNAL(pause()), this, SLOT(emitPropertiesChanged()));
    syncProperties();
    updateId();
}

Player2Object::~Player2Object()
{}

bool Player2Object::canControl() const {
    return false;
}

bool Player2Object::canGoNext() const {
    return true;
}

bool Player2Object::canGoPrevious() const {
    return true;
}

bool Player2Object::canPause() const {
    return true;
}

bool Player2Object::canPlay() const {
    return false;
}


bool Player2Object::canSeek() const {
    return false;
}

double Player2Object::maximumRate() const {
    return 1.0;
}

QVariantMap Player2Object::metadata() const {
    QVariantMap map;
    if (!artist.isEmpty())
        map["xesam:artist"] = QStringList() << artist;
    if (!title.isEmpty())
        map["xesam:title"] =  title;
    map["mpris:trackid"] = m_trackID.path();
    return map;
}

double Player2Object::minimumRate() const {
    return 1.0;
}

QString Player2Object::playbackStatus() const {
    if (playstate)
        return "Playing";
    else if (playstarted)
        return "Paused";
    return "Stopped";
}

void Player2Object::Next() {
    playstate = true;
    emit next();
}

void Player2Object::Pause() {
    playstate = !playstate;
    emit pause();
}

void Player2Object::Play() {
}

void Player2Object::PlayPause() {
    playstate = !playstate;
    emit pause();
}

void Player2Object::Previous() {
    playstate = true;
    emit previous();
}

void Player2Object::Stop() {
}

void Player2Object::Seek(qlonglong) {
}

void Player2Object::SetPosition(const QDBusObjectPath &, qlonglong) {
}

void Player2Object::SongChanged(QString artist, QString title) {
    this->artist = artist;
    this->title = title;
}

void Player2Object::SetPlayState(bool playstate) {
    this->playstarted = true;
    this->playstate = playstate;
}

void Player2Object::emitPropertiesChanged() {
    QList<QByteArray> changedProps;
    if (m_props["canGoNext"] != canGoNext())
        changedProps << "canGoNext";
    if (m_props["canGoPrevious"] != canGoPrevious())
        changedProps << "canGoPrevious";
    if (m_props["canPause"] != canPause())
        changedProps << "canPause";
    if (m_props["canPlay"] != canPlay())
        changedProps << "canPlay";
    if (m_props["canSeek"] != canSeek())
        changedProps << "canSeek";
    if (m_props["playbackStatus"] != playbackStatus())
        changedProps << "playbackStatus";
    if (m_props["position"] != position())
        changedProps << "position";
    if (m_props["metadata"] != metadata())
        changedProps << "metadata";
    syncProperties();
    if (changedProps.isEmpty())
        return;
    QVariantMap map;
    foreach(QByteArray name, changedProps)
    map.insert(name, m_props.value(name));
    QDBusMessage msg;
    msg = QDBusMessage::createSignal("/org/mpris/MediaPlayer2",
                                     "org.freedesktop.DBus.Properties", "PropertiesChanged");
    QVariantList args = QVariantList()
                        << "org.mpris.MediaPlayer2.Player"
                        << map
                        << QStringList();
    msg.setArguments(args);
    QDBusConnection::sessionBus().send(msg);
}

void Player2Object::updateId() {
    if (prevart != artist && prevtitle != title) {
        m_trackID .setPath(QString("%1/Track/%2").arg("/org/mpris/MediaPlayer2").arg(qrand()));
        prevart = this->artist;
        prevtitle = this->title;
    }
}

void Player2Object::syncProperties() {
    m_props["canGoNext"] = canGoNext();
    m_props["canGoPrevious"] = canGoPrevious();
    m_props["canPause"] = canPause();
    m_props["canPlay"] = canPlay();
    m_props["canSeek"] = canSeek();
    m_props["playbackStatus"] = playbackStatus();
    m_props["position"] = position();
    m_props["metadata"] = metadata();
}

qlonglong Player2Object::position() const {
    return 0;
}

double Player2Object::rate() const {
    return 1.0;
}

void Player2Object::setRate(double value) {
    Q_UNUSED(value)
}

double Player2Object::volume() const {
    return 1.0;
}

void Player2Object::setVolume(double value) {
    Q_UNUSED(value)
}
