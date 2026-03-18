#include "directiondialog.h"
#include "ui_directiondialog.h"

#include <QDoubleValidator>

//-----------------------------------------------------------------------------
//
DirectionDialog::DirectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DirectionDialog)
{
    ui->setupUi(this);
    ui->lineEdit_X->setValidator(new QDoubleValidator(0.0, 1.0, 3, this));
    ui->lineEdit_Y->setValidator(new QDoubleValidator(0.0, 1.0, 3, this));
    ui->lineEdit_Z->setValidator(new QDoubleValidator(0.0, 1.0, 3, this));

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DirectionDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DirectionDialog::reject);
}
//-----------------------------------------------------------------------------
//
DirectionDialog::~DirectionDialog()
{
    delete ui;
}
//-----------------------------------------------------------------------------
//
QVector3D DirectionDialog::direction() const
{
   return QVector3D(ui->lineEdit_X->text().toFloat(),
                    ui->lineEdit_Y->text().toFloat(),
                    ui->lineEdit_Z->text().toFloat()).normalized();
}
//-----------------------------------------------------------------------------
//
void DirectionDialog::setDirection(const QVector3D &direction) const
{
    QString sX, sY, sZ;
    sX.setNum(direction.x(), 'f', 3);
    sY.setNum(direction.y(), 'f', 3);
    sZ.setNum(direction.z(), 'f', 3);

    ui->lineEdit_X->setText(sX);
    ui->lineEdit_Y->setText(sY);
    ui->lineEdit_Z->setText(sZ);
}
