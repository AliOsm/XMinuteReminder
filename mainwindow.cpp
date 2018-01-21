#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sbXValue->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->sbIterations->setButtonSymbols(QAbstractSpinBox::NoButtons);

    Helpers::centerWindow(this);

    createActions();
    createTrayIconMenu();
    createTrayIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbStartReminder_clicked()
{
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(runSound()));
    timer->start(ui->sbXValue->value() * 60000);

    if(ui->rbAllowIterations->isChecked()) {
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(decreaseIterations()));
        iterations = ui->sbIterations->value();
    }

    if(QSystemTrayIcon::isSystemTrayAvailable()) {
        Helpers::sayMessage("Where you can find the program?",
                            "You can stop or quit the program using the bell icon beside system clock.",
                            QMessageBox::Information);

        trayIcon->setVisible(true);
        this->hide();
    }
}

void MainWindow::on_rbAllowIterations_clicked(bool checked)
{
    if(checked) {
        ui->sbIterations->setEnabled(true);
    } else {
        ui->sbIterations->setEnabled(false);
        ui->sbIterations->setValue(10);
    }
}

void MainWindow::runSound()
{
    QSound::play(":/Beep/beep.wav");
}

void MainWindow::stop()
{
    this->show();
    trayIcon->setVisible(false);
    timer->stop();
    QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(runSound()));
    delete timer;
}

void MainWindow::decreaseIterations()
{
    if(--iterations == 0) {
        stop();
    }
}

void MainWindow::createActions()
{
    stopAction = new QAction(tr("&Stop"), this);
    connect(stopAction, SIGNAL(triggered()), this, SLOT(stop()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainWindow::createTrayIconMenu()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(stopAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
}

void MainWindow::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/Icon/icon30.png"));
    trayIcon->setContextMenu(trayIconMenu);
}
