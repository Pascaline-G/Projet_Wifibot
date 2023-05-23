#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , robot(parent)
{
    ui->setupUi(this);
    this->ui->LEAdresse->setText("192.168.10.1");
    timerID = this->startTimer(100);
}

MainWindow::~MainWindow()
{
    this->killTimer(timerID);
    delete ui;
}


void MainWindow::on_pBcon_clicked()
{
    bool ok;
    QString adress = ui->LEAdresse->text();
    QString portString = ui->LEPort->text();
    int port = portString.toInt(&ok);
    if(ok){
        robot.doConnect(adress, port);
        this->show_Message_Notif("Connecter à l'adresse " + adress + ":"+ portString);
        QWebEngineView *webEngineView = new QWebEngineView(this);
        webEngineView->resize(500,200);
        ui->verticalLayout_2->addWidget(webEngineView);
        webEngineView->load(QUrl("http://" + adress + ":8080/?action=stream"));
        webEngineView->show();
    }
    else{
        this->show_Message_Error("Le port n'est pas un entier !");
    }
}


void MainWindow::on_pbDeco_clicked()
{
    robot.disConnect();
}

void MainWindow::show_Message_Error(QString message)
{
    QMessageBox messageBox;
    messageBox.critical(0,"Erreur","Le port n'est pas un entier");
    messageBox.setFixedSize(400,200);
}

void MainWindow::show_Message_Notif(QString message)
{
    QMessageBox messageBox;
    messageBox.information(0,"Notification",message);
    messageBox.setFixedSize(500,200);
}


void MainWindow::on_pBForward_pressed()
{
    robot.goForward(120);
    qDebug() << "forward pressed";
}


void MainWindow::on_pbLeft_pressed()
{
    robot.goLeft(120);
    qDebug() << "left pressed";
}


void MainWindow::on_pbBackward_pressed()
{
    robot.goBackward(120);
    qDebug() << "backward pressed";
}


void MainWindow::on_pbRight_pressed()
{
    robot.goRight(120);
    qDebug() << "right pressed";
}


void MainWindow::on_pBForward_released()
{
    robot.stop();
    qDebug() << "Stop";
}


void MainWindow::on_pbLeft_released()
{
    robot.stop();
    qDebug() << "Stop";
}


void MainWindow::on_pbRight_released()
{
    robot.stop();
    qDebug() << "Stop";
}


void MainWindow::on_pbBackward_released()
{
    robot.stop();
    qDebug() << "Stop";
}

void MainWindow::timerEvent(QTimerEvent *event) {
    this->updateDisplayDataRobot();
}

void MainWindow::updateDisplayDataRobot() {
    MyRobotData robotData = robot.readData();
    QString vitesseL = QString::number(robotData.dataL.speedFront);
    QString vitesseR = QString::number(robotData.dataR.speedFront);

    this->ui->label_vitesse->setText("(" + vitesseL + ", " + vitesseR  +  ")");

    QString bat = QString::number(robotData.batLevel);
    this->ui->label_bat->setText(bat);

    QString odometrieL = QString::number(robotData.dataL.odometry);
    QString odometrieR = QString::number(robotData.dataR.odometry);
    this->ui->label_odometrie->setText("(" + odometrieL + ", " + odometrieR  +  ")");
}

void MainWindow::on_pBAffichInfo_clicked()
{
    this->updateDisplayDataRobot();
}

