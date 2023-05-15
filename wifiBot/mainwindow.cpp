#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , robot(parent)
{
    ui->setupUi(this);
    this->ui->LEAdresse->setText("192.168.10.1");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pBcon_clicked()
{

    bool ok;
    QString adress = ui->LEAdresse->text();
    QString portString = ui->LEPort->text();
    int port = portString.toInt(&ok);
    QString message = "Le port n est pas un entier !";
    if(ok){
        robot.doConnect(adress, port);
        this->show_Message_Notif("Connecter à l'adresse " + adress + ":"+ portString);
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
    messageBox.setFixedSize(500,200);
}

void MainWindow::show_Message_Notif(QString message)
{
    QMessageBox messageBox;
    messageBox.information(0,"Notification",message);
    messageBox.setFixedSize(500,200);
}

void MainWindow::on_pBForward_clicked()
{
    robot.goForward(120);
    qDebug() << "forward clicked";
}


void MainWindow::on_pbBackward_clicked()
{
    robot.goBackward(120);
    qDebug() << "backward clicked";
}


void MainWindow::on_pbRight_clicked()
{
    robot.goRight(120);
    qDebug() << "right clicked";
}


void MainWindow::on_pbLeft_clicked()
{
    robot.goLeft(120);
    qDebug() << "left clicked";
}

