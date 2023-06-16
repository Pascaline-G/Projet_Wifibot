#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , robot(parent)
    , isConnected(false)
    , webEngineView(nullptr)
{
    ui->setupUi(this);

    //Initialisation de l'adresse pour se connecter
    this->ui->LEAdresse->setText("192.168.1.106");
    this->ui->LEPort->setText("15020");

    //Permet de controler le robot avec le clavier
    AllowControleKeyboard(this->ui->centralwidget);
}

//object destructor to free memory
MainWindow::~MainWindow()
{
    if(isConnected) {
        this->killTimer(timerID);
        robot.disConnect();
        isConnected = false;
        if(webEngineView) {
            this->webEngineView->stop();
            delete webEngineView;
            webEngineView = nullptr;
        }
    }
    delete ui;
}


//function who set a callback, to each object in the ui, to catch keyboard input
void MainWindow::AllowControleKeyboard(QObject *object){
    const QObjectList &localChildren = object->children();

    foreach (QObject *obj, localChildren) {
        obj->installEventFilter(this);
        AllowControleKeyboard(obj);
    }
}

//Connexion avec le robot en cliquant sur le bouton
void MainWindow::on_pBcon_clicked()
{
    QString adress = ui->LEAdresse->text();
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

            //supression de l'ancien webEngine avant d'en créer un nouveau
            if(webEngineView) {
                ui->verticalLayout_2->removeWidget(webEngineView);
                delete webEngineView;
            }
            //Ajout emplacement de la caméra
            webEngineView = new QWebEngineView();
            webEngineView->resize(500,200);
            ui->verticalLayout_2->addWidget(webEngineView);
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

//Deconnexion avec le robot en cliquant sur le bouton
void MainWindow::on_pbDeco_clicked()
{
    if(isConnected) {
        //Déconnexion du robot
        robot.disConnect();
        isConnected = false;

        //Fin de la caméra
        if(webEngineView) {
            //display white screen
            webEngineView->load(QUrl(""));
            webEngineView->show();
        }
    }
}

//Affichage d'un message d'erreur
void MainWindow::show_Message_Error(QString message)
{
    QMessageBox messageBox;
    messageBox.critical(0,"Erreur", message);
    messageBox.setFixedSize(400,200);
}

//Affichage d'une notification
void MainWindow::show_Message_Notif(QString message)
{
    QMessageBox messageBox;
    messageBox.information(0,"Notification",message);
    messageBox.setFixedSize(500,200);
}

//Bouton pressé pour avancer
void MainWindow::on_pBForward_pressed()
{
    int vitesse = ui->SliderVitesse->value();
    qDebug() << "---------------------------------------------Vitesse :" << vitesse;
    robot.goForward(vitesse);
    qDebug() << "forward pressed";
}

//Bouton pressé pour tourner à gauche
void MainWindow::on_pbLeft_pressed()
{
    int vitesse = ui->SliderVitesse->value();
    robot.goLeft(vitesse);
    qDebug() << "left pressed";
}

//Bouton pressé pour reculer
void MainWindow::on_pbBackward_pressed()
{
    int vitesse = ui->SliderVitesse->value();
    robot.goBackward(vitesse);
    qDebug() << "backward pressed";
}

//Bouton pressé pour aller à droite
void MainWindow::on_pbRight_pressed()
{
    int vitesse = ui->SliderVitesse->value();
    robot.goRight(vitesse);
    qDebug() << "right pressed";
}

//Relacher le bouton avancer pour s'arrêter
void MainWindow::on_pBForward_released()
{
    robot.stop();
    qDebug() << "Stop";
}


//Relacher le bouton pour tourner à gauche pour s'arrêter
void MainWindow::on_pbLeft_released()
{
    robot.stop();
    qDebug() << "Stop";
}


//Relacher le bouton pour tourner à droite pour s'arrêter
void MainWindow::on_pbRight_released()
{
    robot.stop();
    qDebug() << "Stop";
}


//Relacher le bouton reculer pour s'arrêter
void MainWindow::on_pbBackward_released()
{
    robot.stop();
    qDebug() << "Stop";
}

//function built in by qt. This update UI every 100millisecond
void MainWindow::timerEvent(QTimerEvent *event) {
    this->updateDisplayDataRobot();
}

//Met à jour l'affichage des donnée de robot (Vitesse, position, batterie, InfraRouge)
void MainWindow::updateDisplayDataRobot() {
    if(isConnected) {
        MyRobotData robotData = robot.readData();
        QString puissanceL = QString::number(robotData.dataL.speedFront);
        QString puissanceR = QString::number(robotData.dataR.speedFront);
        this->ui->label_puissance->setText("(" + puissanceL + ", " + puissanceR +  ")");


        //normalize bat level
        float batLevel = (robotData.batLevel / 255.0) * 100.0;
        QString bat = QString::number(batLevel);
        this->ui->label_bat->setText(bat);


        //compute the speed with odometrie
        long odo_diff_l = robotData.dataL.odometry - robotData.dataL.previousOdometry;
        long odo_diff_r = robotData.dataR.odometry - robotData.dataR.previousOdometry;
        float time = 0.1; //100ms
        float dist_tic = 0.44/2048.0;

        QString vitesseL = QString::number(odo_diff_l * dist_tic / time);
        QString vitesseR = QString::number(odo_diff_r * dist_tic / time);

        this->ui->label_vitesse->setText("(" + vitesseL + "m/s, " + vitesseR  +  "m/s)");

        //Odométrie
        QString odometrieL = QString::number(robotData.dataL.odometry);
        QString odometrieR = QString::number(robotData.dataR.odometry);
        this->ui->label_odometrie->setText("(" + odometrieL + ", " + odometrieR  +  ")");

        //Infrarouge
        QString infraL1 = QString::number(robotData.dataL.IR);
        QString infraL2 = QString::number(robotData.dataL.IR2);

        QString infraR1 = QString::number(robotData.dataR.IR);
        QString infraR2 = QString::number(robotData.dataR.IR2);

        //Affichage des données
        this->ui->label_infra->setText("(" + infraL1 + ", " + infraL2 + ", " + infraR1 + ", " + infraR2 +  ")");
    }
}


//Bouton de mise à jour manuelle de l'affichage des données du Robot
void MainWindow::on_pBAffichInfo_clicked()
{
    this->updateDisplayDataRobot();
}


//Permet de filtrer les évenements et donc les input du clavier en fonction de leur type (pressé ou relaché)
bool MainWindow::eventFilter(QObject *obj, QEvent *e){

    if(e->type() == QEvent::KeyPress){

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        HandleKeyPress(keyEvent);
    }
    if(e->type() == QEvent::KeyRelease){

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        handleKeyRelease(keyEvent);
    }
    return false;
}

//Gèrent qu'elle action effectuer en fonction de la touche du clavier qui est pressée
void MainWindow::HandleKeyPress(QKeyEvent *event)
{
    int vitesse = 0;
    switch(event->key())
    {
    case 16777235:
        qDebug("Go UP");
        vitesse = ui->SliderVitesse->value();
        robot.goForward(vitesse);
        break;
    case 16777237:
        qDebug("Go Down");
        vitesse = ui->SliderVitesse->value();
        robot.goBackward(vitesse);
        break;
    case Qt::LeftArrow : case 16777234:
        vitesse = ui->SliderVitesse->value();
        qDebug("Go left");
        robot.goLeft(vitesse);
        break;
    case 16777236:
        qDebug("Go right");
        vitesse = ui->SliderVitesse->value();
        robot.goRight(vitesse);
        break;
    default:
        qDebug("Key pressed not implemented");
        break;
    }
    if(event->key() == 16777234){
        qDebug("Go left");
    }
}

//Gèrent qu'elle action effectuer en fonction de la touche du clavier qui est relachée
void MainWindow::handleKeyRelease(QKeyEvent *event)
{
    qDebug() << event->key();
    switch(event->key())
    {
    case 16777234 : case 16777235 : case 16777237 : case 16777236:
        robot.stop();
        break;
    default:
        qDebug("Key released not implemented");
        break;
    }
}

//Bouton pour bouger la caméra vers le haut
void MainWindow::on_pBMoveCamUp_clicked()
{
    robot.MoveCamUp();
}


//Bouton pour bouger la caméra vers la droite
void MainWindow::on_pBMoveCamRight_clicked()
{
    robot.MoveCamRight();
}


//Bouton pour bouger la caméra vers le bas
void MainWindow::on_pBMoveCamDown_clicked()
{
    robot.MoveCamDown();
}


//Bouton pour bouger la caméra vers la gauche
void MainWindow::on_pBMoveCamLeft_clicked()
{
    robot.MoveCamLeft();
}


//Bouton pour afficher une nouvelle fenêtre pour modifier l'image
void MainWindow::on_pBControleImage_clicked()
{
    if(isConnected){
        ControleImage mDialog;
        mDialog.setModal(true);
        mDialog.exec();
    }
}

