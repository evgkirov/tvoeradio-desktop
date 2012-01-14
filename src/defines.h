#ifndef DEFINES_H
#define DEFINES_H

#include <QUrl>

#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<Application *>(QCoreApplication::instance()))

#define u(s) QString::fromUtf8(s)

#define APP_TITLE u("Твоёрадио")
#define APP_NAME "tvoeradio-desktop"
#define APP_VERSION "2.0a"
#define APP_ORG "tvoeradio"
#define APP_DOMAIN "tvoeradio.org"
#define APP_URL QUrl("http://tvoeradio.org/app/")

#endif // DEFINES_H
