// myrobot.cpp

#include "myrobot.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


void MyRobot::doConnect(QString address, int port) {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    socket->connectToHost(address, port); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);
}

//robot goes straight fordward
void MyRobot::goForward(char speed) {
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = speed;
    DataToSend[3] = speed;
    DataToSend[4] = speed;
    DataToSend[5] = speed;
    DataToSend[6] = 80;     //control the direction 0101 0000

    short crc = Crc16(DataToSend.data() + 1, 6);
    DataToSend[7] = crc & 0x00ff;
    DataToSend[8] = (crc & 0xff00)>>8;
}

//robot goes straight backward
void MyRobot::goBackward(char speed) {
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = speed;
    DataToSend[3] = speed;
    DataToSend[4] = speed;
    DataToSend[5] = speed;
    DataToSend[6] = 0;      //control the direction 0000 0000

    short crc = Crc16(DataToSend.data() + 1, 6);
    DataToSend[7] = crc & 0x00ff;
    DataToSend[8] = (crc & 0xff00)>>8;

}

void MyRobot::goRight(char speed) {
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = speed;
    DataToSend[3] = speed;
    DataToSend[4] = speed;
    DataToSend[5] = speed;
    DataToSend[6] = 64;     //control the direction 0100 0000


    short crc = Crc16(DataToSend.data() + 1, 6);
    DataToSend[7] = crc & 0x00ff;
    DataToSend[8] = (crc & 0xff00)>>8;
}

void MyRobot::goLeft(char speed) {
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = speed;
    DataToSend[3] = speed;
    DataToSend[4] = speed;
    DataToSend[5] = speed;
    DataToSend[6] = 16;     //control the direction 0001 0000

    short crc = Crc16(DataToSend.data() + 1, 6);
    DataToSend[7] = crc & 0x00ff;
    DataToSend[8] = (crc & 0xff00)>>8;

}

void MyRobot::stop(){
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0;
    DataToSend[3] = 0;
    DataToSend[4] = 0;
    DataToSend[5] = 0;
    DataToSend[6] = 0;

    short crc = Crc16(DataToSend.data() + 1, 6);
    DataToSend[7] = crc & 0x00ff;
    DataToSend[8] = (crc & 0xff00)>>8;
}

//method to calculate crc. Give by documentation
short MyRobot::Crc16(char *tab, unsigned char size) const {
    unsigned int crc = 0xFFFF;
    unsigned int polyome = 0xA001;
    unsigned int cptOctet = 0;
    unsigned int cptBit = 0;
    unsigned int parity = 0;

    for(cptOctet = 0; cptOctet < size; cptOctet++) {
        crc ^= *(tab + cptOctet);
        for(cptBit = 0; cptBit <= 7; cptBit++) {
            parity = crc;
            crc >>= 1;

            if(parity % 2) {
                crc ^= polyome;
            }
        }
    }

    return crc;
}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

