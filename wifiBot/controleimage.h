#ifndef CONTROLEIMAGE_H
#define CONTROLEIMAGE_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class ControleImage;
}

class ControleImage : public QDialog
{
    Q_OBJECT

public:
    explicit ControleImage(QWidget *parent = nullptr);
    ~ControleImage();

private slots:
    void on_sBLuminosite_editingFinished();

    void on_sBContraste_editingFinished();

    void on_sBSaturation_editingFinished();

    void on_pBNoirEtBlanc_clicked();

    void on_pBCouleur_clicked();

    void on_sBNet_editingFinished();

    void on_sBFocus_editingFinished();

    void on_pBPsychdlique_clicked();

    void on_pBReinit_clicked();

private:
    Ui::ControleImage *ui;
    QNetworkAccessManager *manager;
};

#endif // CONTROLEIMAGE_H
