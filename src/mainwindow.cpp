#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->s_settingsDialog = 0;

    this->setWindowTitle(APP_TITLE);
    this->setMinimumSize(627, 500);

    this->view = new WebView(this);
    this->view->setUrl(APP_URL);
    this->setCentralWidget(this->view);
    this->view->show();
    connect(this->view, SIGNAL(titleChanged(QString)), this, SLOT(setWindowTitle(QString)));

#ifndef Q_WS_MAC

    // Global keys

    QxtGlobalShortcut* previousMediaShortcut = new QxtGlobalShortcut(QKeySequence("Media Previous"));
    connect(previousMediaShortcut, SIGNAL(activated()), qApp->bridge, SIGNAL(previous()));

    QxtGlobalShortcut* previousShortcut = new QxtGlobalShortcut(QKeySequence("Meta+F10"));
    connect(previousShortcut, SIGNAL(activated()), qApp->bridge, SIGNAL(previous()));

    QxtGlobalShortcut* playMediaShortcut = new QxtGlobalShortcut(QKeySequence("Media Play"));
    connect(playMediaShortcut, SIGNAL(activated()), qApp->bridge, SIGNAL(pause()));

    QxtGlobalShortcut* playShortcut = new QxtGlobalShortcut(QKeySequence("Meta+F11"));
    connect(playShortcut, SIGNAL(activated()), qApp->bridge, SIGNAL(pause()));

    QxtGlobalShortcut* nextMediaShortcut = new QxtGlobalShortcut(QKeySequence("Media Next"));
    connect(nextMediaShortcut, SIGNAL(activated()), qApp->bridge, SIGNAL(next()));

    QxtGlobalShortcut* nextShortcut = new QxtGlobalShortcut(QKeySequence("Meta+F12"));
    connect(nextShortcut, SIGNAL(activated()), qApp->bridge, SIGNAL(next()));


#endif

    // Tray menu

    QMenu *menu = new QMenu();

    QAction *activateAction = menu->addAction(u("Активиров&ать"));
    connect(activateAction, SIGNAL(triggered()), this, SLOT(showAndRaise()));

    menu->addSeparator();

    QAction *trackArtistAction = menu->addAction("");
    trackArtistAction->setEnabled(false);
    trackArtistAction->setVisible(false);
    connect(qApp->bridge, SIGNAL(playing_change(bool)), trackArtistAction, SLOT(setVisible(bool)));

    QAction *trackTitleAction = menu->addAction("");
    trackTitleAction->setEnabled(false);
    trackTitleAction->setVisible(false);
    connect(qApp->bridge, SIGNAL(playing_change(bool)), trackTitleAction, SLOT(setVisible(bool)));

    QAction *previousTrackAction = menu->addAction(u("П&редыдущий трек"));
    previousTrackAction->setEnabled(false);
    connect(previousTrackAction, SIGNAL(triggered()), qApp->bridge, SIGNAL(previous()));
    connect(qApp->bridge, SIGNAL(playing_change(bool)), previousTrackAction, SLOT(setEnabled(bool)));

    QAction *playPauseAction = menu->addAction(u("Пауза/продолж&ить"));
    playPauseAction->setEnabled(false);
    connect(playPauseAction, SIGNAL(triggered()), qApp->bridge, SIGNAL(pause()));
    connect(qApp->bridge, SIGNAL(playing_change(bool)), playPauseAction, SLOT(setEnabled(bool)));

    QAction *nextTrackAction = menu->addAction(u("С&ледующий трек"));
    nextTrackAction->setEnabled(false);
    connect(nextTrackAction, SIGNAL(triggered()), qApp->bridge, SIGNAL(next()));
    connect(qApp->bridge, SIGNAL(playing_change(bool)), nextTrackAction, SLOT(setEnabled(bool)));

    menu->addSeparator();

    QAction *settingsDialogAction = menu->addAction(u("Уведомления и прокси..."));
    connect(settingsDialogAction, SIGNAL(triggered()), this, SLOT(settingsDialog()));

    QAction *quitAction = menu->addAction(u("В&ыход"));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(qApp->bridge, SIGNAL(track_change(QString,QString)), this, SLOT(notify(QString,QString)));

    this->systemTrayIcon = new QSystemTrayIcon();
    this->systemTrayIcon->setContextMenu(menu);
    #ifdef Q_WS_MAC
        this->systemTrayIcon->setIcon(QIcon(":/icon16-mac"));
    #endif
    #ifndef Q_WS_MAC
        this->systemTrayIcon->setIcon(QIcon(":/icon16"));
        connect(this->systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(showAndRaise(QSystemTrayIcon::ActivationReason)));
        //mainWindow.setWindowIcon(icon);
    #endif
    this->systemTrayIcon->show();

}

MainWindow::~MainWindow()
{
    delete this->systemTrayIcon;
    delete this->view;
}

void MainWindow::showAndRaise()
{
    this->show();
    this->raise();
}

void MainWindow::showAndRaise(QSystemTrayIcon::ActivationReason reason)
{
    if (QSystemTrayIcon::Trigger == reason)
        this->showAndRaise();
}

void MainWindow::notify(QString artist, QString title)
{
    QSettings settings;
    if (settings.value("Interface/Notifications", true).toBool()) {
        this->systemTrayIcon->showMessage(title, artist, QSystemTrayIcon::NoIcon, 2000);
    }
    this->systemTrayIcon->contextMenu()->actions()[2]->setText(artist);
    this->systemTrayIcon->contextMenu()->actions()[3]->setText(title);
}

void MainWindow::settingsDialog()
{
    if (!this->s_settingsDialog) {
        this->s_settingsDialog = new SettingsDialog(this);
    }
    this->s_settingsDialog->show();
}
