#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./driversWifiBot/myrobot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pBcon_clicked();
    void on_pbDeco_clicked();

private:
    Ui::MainWindow *ui;
    MyRobot robot;
};
#endif // MAINWINDOW_H
