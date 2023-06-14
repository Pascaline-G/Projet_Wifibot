#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QString>
#include <QNetworkAccessManager>

struct SideData {
    int speedFront;
    unsigned char IR;
    unsigned char IR2;
    long odometry;
};


//struct to stock data received from robot
struct MyRobotData {
    SideData dataL;
    SideData dataR;
    unsigned char batLevel;
};


class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    bool doConnect(QString adress, int port);
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

    void goForward(char speed);
    void goBackward(char speed);
    void goRight(char speed);
    void goLeft(char speed);

    void stop();

    void MoveCamRight();
    void MoveCamLeft();
    void MoveCamUp();
    void MoveCamDown();

    MyRobotData readData() const;

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();

private:
    short Crc16(char *tab, unsigned char size) const;
    QNetworkAccessManager *manager;
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
};

#endif // MYROBOT_H
