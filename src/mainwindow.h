#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QSettings>
#include <QSystemTrayIcon>
#include "qxtglobalshortcut.h"
#include "application.h"
#include "defines.h"
#include "settingsdialog.h"
#include "webview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMainWindow *mainWindow;
    WebView *view;
    QSystemTrayIcon *systemTrayIcon;

private:
    SettingsDialog *s_settingsDialog;

public slots:
    void setWindowTitle(const QString &);
    void showAndRaise();
    void showAndRaise(QSystemTrayIcon::ActivationReason reason);
    void notify(QString artist, QString title);
    void settingsDialog();


};

#endif // MAINWINDOW_H
