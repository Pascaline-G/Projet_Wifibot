#include "controleimage.h"
#include "./ui_controleimage.h"

//Fenêtre pour modifier l'image de la caméra du robot.
ControleImage::ControleImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControleImage)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
}

ControleImage::~ControleImage()
{
    delete ui;
    if(manager) {
        delete manager;
        manager = nullptr;
    }
}

//Met à jour la luminosité dans l'utilisateur à fini de modifier la valeur
void ControleImage::on_sBLuminosite_editingFinished()
{
    QString value = QString::number(ui->sBLuminosite->value());
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963776&group=1&value="+value)));
}


//Met à jour le contraste dans l'utilisateur à fini de modifier la valeur
void ControleImage::on_sBContraste_editingFinished()
{
    QString value = QString::number(ui->sBContraste->value());
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963777&group=1&value="+value)));
}


//Met à jour la saturation dans l'utilisateur à fini de modifier la valeur
void ControleImage::on_sBSaturation_editingFinished()
{
    QString value = QString::number(ui->sBSaturation->value());
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963778&group=1&value="+value)));
}



//Bouton pour mettre l'image de la caméra en noir et blanc
void ControleImage::on_pBNoirEtBlanc_clicked()
{
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963778&group=1&value=0")));
}

//Bouton pour mettre l'image en couleur
void ControleImage::on_pBCouleur_clicked()
{
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963778&group=1&value=32")));
}


//Met à jour la netteté dans l'utilisateur à fini de modifier la valeur
void ControleImage::on_sBNet_editingFinished()
{
    QString value = QString::number(ui->sBNet->value());
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963803&group=1&value="+value)));
}


//Met à jour le focus dans l'utilisateur à fini de modifier la valeur
void ControleImage::on_sBFocus_editingFinished()
{
    QString value = QString::number(ui->sBFocus->value());
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=168062212&group=1&value="+value)));
}

//Bouton pour mettre donner à l'image un aspet psichédélique
void ControleImage::on_pBPsychdlique_clicked()
{
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963776&group=1&value=50"))); //Luminosité
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963777&group=1&value=255"))); //Contraste
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963778&group=1&value=255"))); // Saturation


}

//Bouton pour réinitialiser les paramètres de la caméra
void ControleImage::on_pBReinit_clicked()
{
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963776&group=1&value=200"))); //Luminosité
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963777&group=1&value=32"))); //Contraste
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963778&group=1&value=32"))); // Saturation
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=168062212&group=1&value=0")));//Focus
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963803&group=1&value=255")));

}

