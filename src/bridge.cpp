#include "bridge.h"

Bridge::Bridge(QObject *parent) :
    QObject(parent)
{
}

QString Bridge::get_version()
{
    return qApp->applicationVersion();
}

QVariantMap Bridge::get_palette()
{
    QVariantMap colors;
    QPalette palette = qApp->palette();
    colors.insert("window", palette.window().color().name());
    colors.insert("window_text", palette.windowText().color().name());
    colors.insert("base", palette.base().color().name());
    colors.insert("alternate_base", palette.alternateBase().color().name());
    colors.insert("text", palette.text().color().name());
    colors.insert("button", palette.buttonText().color().name());
    colors.insert("bright_text", palette.brightText().color().name());
    colors.insert("light", palette.light().color().name());
    colors.insert("midlight", palette.midlight().color().name());
    colors.insert("dark", palette.dark().color().name());
    colors.insert("mid", palette.mid().color().name());
    colors.insert("shadow", palette.shadow().color().name());
    colors.insert("highlight", palette.highlight().color().name());
    colors.insert("highlight_text", palette.highlightedText().color().name());
    colors.insert("link", palette.link().color().name());
    colors.insert("link_visited", palette.linkVisited().color().name());
    return colors;
}

void Bridge::logout()
{
    this->networkCookieJar->clear();
}
