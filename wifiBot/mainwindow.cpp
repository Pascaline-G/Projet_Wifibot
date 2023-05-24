#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , robot(parent)
    , isConnected(false)
    , webEngineView(new QWebEngineView(this))
{
    ui->setupUi(this);
    //Set an address
    this->ui->LEAdresse->setText("192.168.1.106");
    webEngineView->resize(500,200);
    ui->verticalLayout_2->addWidget(webEngineView);

    //load fake url to show white image on screen. Needed but don't know why
    webEngineView->load(QUrl(""));
    webEngineView->show();
    
    timerID = this->startTimer(100);
}

MainWindow::~MainWindow()
{
    if(isConnected) {
        this->killTimer(timerID);
        robot.disConnect();
        isConnected = false;
        if(webEngineView) {
            this->webEngineView->stop();
            //delete webEngineView;
            //webEngineView = nullptr;
        }
    }
    delete ui;
}

//Connection button
void MainWindow::on_pBcon_clicked()
{
    QString adress = ui->LEAdresse->text();

    //Check if port input is an int
    bool ok;
    QString portString = ui->LEPort->text();

    bool ok;
    int port = portString.toInt(&ok);
    if(ok){
        //connexion au robot
        isConnected = robot.doConnect(adress, port);
        if(isConnected) {
            this->show_Message_Notif("Connecter à l'adresse " + adress + ":"+ portString);

            //lancement du timer pour update l'ui
            timerID = this->startTimer(100);

            //récupération et affichage de la caméra
            webEngineView->load(QUrl("http://" + adress + ":8080/?action=stream"));
            webEngineView->show();
        }
        else {
            this->show_Message_Error("Impossible de se connecter");
        }
    }
    else{
        this->show_Message_Error("Le port n'est pas un entier !");
    }
}

//Deco button
void MainWindow::on_pbDeco_clicked()
{
    if(isConnected) {
        robot.disConnect();
        isConnected = false;
        if(webEngineView) {
            this->webEngineView->stop();

            //display white screen
            webEngineView->load(QUrl(""));
            webEngineView->show();
        }
    }
}

//Display error message
void MainWindow::show_Message_Error(QString message)
{
    QMessageBox messageBox;
    messageBox.critical(0,"Erreur", message);
    messageBox.setFixedSize(400,200);
}

//Deplay notification
void MainWindow::show_Message_Notif(QString message)
{
    QMessageBox messageBox;
    messageBox.information(0,"Notification",message);
    messageBox.setFixedSize(500,200);
}

//Go forward button
void MainWindow::on_pBForward_pressed()
{
    robot.goForward(120);
    qDebug() << "forward pressed";
}

//Go left Button
void MainWindow::on_pbLeft_pressed()
{
    robot.goLeft(120);
    qDebug() << "left pressed";
}

//Go backward button
void MainWindow::on_pbBackward_pressed()
{
    robot.goBackward(120);
    qDebug() << "backward pressed";
}

//Go right button
void MainWindow::on_pbRight_pressed()
{
    robot.goRight(120);
    qDebug() << "right pressed";
}

//Robot stop
void MainWindow::on_pBForward_released()
{
    robot.stop();
    qDebug() << "Stop";
}

//Robot stop
void MainWindow::on_pbLeft_released()
{
    robot.stop();
    qDebug() << "Stop";
}

//Robot stop
void MainWindow::on_pbRight_released()
{
    robot.stop();
    qDebug() << "Stop";
}

//Robot stop
void MainWindow::on_pbBackward_released()
{
    robot.stop();
    qDebug() << "Stop";
}

//function built in by qt. This update UI every 100millisecond
void MainWindow::timerEvent(QTimerEvent *event) {
    this->updateDisplayDataRobot();
}

//Update the display of informations from robot
void MainWindow::updateDisplayDataRobot() {
<<<<<<< HEAD
    if(isConnected) {
        //Display speed
        MyRobotData robotData = robot.readData();
        QString vitesseL = QString::number(robotData.dataL.speedFront);
        QString vitesseR = QString::number(robotData.dataR.speedFront);

        this->ui->label_vitesse->setText("(" + vitesseL + ", " + vitesseR  +  ")");

        //Display battery
        QString bat = QString::number(robotData.batLevel);
        this->ui->label_bat->setText(bat);

        //Display odometry
        QString odometrieL = QString::number(robotData.dataL.odometry);
        QString odometrieR = QString::number(robotData.dataR.odometry);
        this->ui->label_odometrie->setText("(" + odometrieL + ", " + odometrieR  +  ")");
    }
}

//Depreciated : Button Update the display of informations from robot
void MainWindow::on_pBAffichInfo_clicked()
{
    this->updateDisplayDataRobot();
}

