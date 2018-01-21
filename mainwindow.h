#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>

#include "helpers.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbStartReminder_clicked();
    void runSound();
    void stop();
    void decreaseIterations();

    void on_rbAllowIterations_clicked(bool checked);

private:
    void createActions();
    void createTrayIconMenu();
    void createTrayIcon();

    Ui::MainWindow *ui;
    QTimer *timer;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *stopAction;
    QAction *quitAction;

    int iterations;
};

#endif // MAINWINDOW_H
