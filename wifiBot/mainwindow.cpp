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



    //robot goes straight forward
    /**robot.DataToSend[0] = 0xFF;
    robot.DataToSend[1] = 0x07;
    robot.DataToSend[2] = 120;
    robot.DataToSend[3] = 0x0;
    robot.DataToSend[4] = 120;
    robot.DataToSend[5] = 0x0;
    robot.DataToSend[6] = 80;
    robot.DataToSend[7] = 0x0;
    robot.DataToSend[8] = 0x0;**/
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

}


void MainWindow::on_pbBackward_clicked()
{

}


void MainWindow::on_pbRight_clicked()
{

}


void MainWindow::on_pbLeft_clicked()
{

}

