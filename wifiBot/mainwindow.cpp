#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , robot(parent)
{
    ui->setupUi(this);
    robot.doConnect();

    //robot goes straight forward
    robot.DataToSend[0] = 0xFF;
    robot.DataToSend[1] = 0x07;
    robot.DataToSend[2] = 120;
    robot.DataToSend[3] = 0x0;
    robot.DataToSend[4] = 120;
    robot.DataToSend[5] = 0x0;
    robot.DataToSend[6] = 80;
    robot.DataToSend[7] = 0x0;
    robot.DataToSend[8] = 0x0;
}

MainWindow::~MainWindow()
{
    robot.disConnect();
    delete ui;
}

