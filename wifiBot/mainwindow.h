#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./driversWifiBot/myrobot.h"
#include <QMessageBox>
#include <QString>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateDisplayDataRobot();

private slots:
    void on_pBcon_clicked();
    void on_pbDeco_clicked();
    void on_pBForward_pressed();
    void on_pbLeft_pressed();
    void on_pbBackward_pressed();
    void on_pbRight_pressed();
    void on_pBForward_released();
    void on_pbLeft_released();
    void on_pbRight_released();
    void on_pbBackward_released();
    void on_pBAffichInfo_clicked();

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;
    MyRobot robot;
    bool isConnected;
    int timerID;
    QWebEngineView *webEngineView;
    void show_Message_Error(QString message);
    void show_Message_Notif(QString message);
    bool eventFilter(QObject *obj, QEvent *e);
    void AllowControleKeyboard(QObject *object);
    void HandleKeyPress(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);


};
#endif // MAINWINDOW_H
