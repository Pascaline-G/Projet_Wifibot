#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./driversWifiBot/myrobot.h"
#include <QMessageBox>
#include <QString.h>

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


    void on_pBForward_clicked();

    void on_pbBackward_clicked();

    void on_pbRight_clicked();

    void on_pbLeft_clicked();

private:
    Ui::MainWindow *ui;
    MyRobot robot;
    void show_Message_Error(QString message);
    void show_Message_Notif(QString message);

};
#endif // MAINWINDOW_H
