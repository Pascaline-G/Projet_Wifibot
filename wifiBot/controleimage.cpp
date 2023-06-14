#include "controleimage.h"
#include "./ui_controleimage.h"

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

void ControleImage::on_sBLuminosite_editingFinished()
{
    QString value = QString::number(ui->sBLuminosite->value());
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963776&group=1&value="+value)));
}


void ControleImage::on_sBContraste_editingFinished()
{
    QString value = QString::number(ui->sBContraste->value());
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963777&group=1&value="+value)));
}


void ControleImage::on_sBSaturation_editingFinished()
{
    QString value = QString::number(ui->sBSaturation->value());
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963778&group=1&value="+value)));
}




void ControleImage::on_pBNoirEtBlanc_clicked()
{
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963778&group=1&value=0")));
}


void ControleImage::on_pBCouleur_clicked()
{
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963778&group=1&value=32")));
}


void ControleImage::on_sBNet_editingFinished()
{
    QString value = QString::number(ui->sBNet->value());
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963803&group=1&value="+value)));
}


void ControleImage::on_sBFocus_editingFinished()
{
    QString value = QString::number(ui->sBFocus->value());
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=168062212&group=1&value="+value)));
}


void ControleImage::on_pBPsychdlique_clicked()
{
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963776&group=1&value=50")));
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963777&group=1&value=255")));
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=9963778&group=1&value=255")));


}

