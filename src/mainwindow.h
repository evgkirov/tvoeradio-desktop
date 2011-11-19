#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include "application.h"
#include "defines.h"
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

public slots:
    void showAndRaise();
    void showAndRaise(QSystemTrayIcon::ActivationReason reason);
    void notify(QString artist, QString title);




};

#endif // MAINWINDOW_H
