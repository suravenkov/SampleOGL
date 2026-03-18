#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "directiondialog.h"
#include "helpdialog.h"
#include "sampleoglwidget.h"

#include <QColorDialog>
#include <QKeyEvent>
#include <QOpenGLFunctions>
#include <QVector3D>

//-----------------------------------------------------------------------------
//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_sampleOGLWidget = new SampleOGLWidget(this);
    ui->horizontalLayout->addWidget(m_sampleOGLWidget);
    m_sampleOGLWidget->setFocus();
}
//-----------------------------------------------------------------------------
//
MainWindow::~MainWindow()
{
    delete ui;
}

//-----------------------------------------------------------------------------
//
void MainWindow::on_pushButton_Color_clicked()
{
    QColorDialog colorDialog;
    QColor newColor = colorDialog.getColor(m_sampleOGLWidget->color(), this);
    if (newColor != QColor::Invalid)
    {
        m_sampleOGLWidget->setColor(newColor);
    }
}
//-----------------------------------------------------------------------------
//
void MainWindow::on_pushButton_xRotate_clicked()
{
    m_sampleOGLWidget->startRotation();
    m_sampleOGLWidget->setRotateAxis(QVector3D(1.0f, 0.0f, 0.0f));
}
//-----------------------------------------------------------------------------
//
void MainWindow::on_pushButton_yRotate_clicked()
{
    m_sampleOGLWidget->startRotation();
    m_sampleOGLWidget->setRotateAxis(QVector3D(0.0f, 1.0f, 0.0f));
}
//-----------------------------------------------------------------------------
//
void MainWindow::on_pushButton_zRotate_clicked()
{
    m_sampleOGLWidget->startRotation();
    m_sampleOGLWidget->setRotateAxis(QVector3D(0.1f, 0.0f, 1.0f).normalized());
}
//-----------------------------------------------------------------------------
//
void MainWindow::on_pushButton_FreeRotate_clicked()
{
    DirectionDialog directionDialog(this);
    directionDialog.setDirection(m_sampleOGLWidget->rotateAxis());
    directionDialog.exec();
    QDialog::DialogCode result = static_cast<QDialog::DialogCode>(directionDialog.result());
    if (result == QDialog::Accepted)
    {
        m_sampleOGLWidget->startRotation();
        m_sampleOGLWidget->setRotateAxis(directionDialog.direction());
    }
}
//-----------------------------------------------------------------------------
//
void MainWindow::on_pushButton_help_clicked()
{
    HelpDialog helpDialog(this);
    helpDialog.exec();
}
//-----------------------------------------------------------------------------
//
void MainWindow::keyPressEvent(QKeyEvent* keyEvent)
{
   switch (keyEvent->key())
   {
      case Qt::Key_Plus:
          m_sampleOGLWidget->scale_plus();
          break;
      case Qt::Key_Minus:
          m_sampleOGLWidget->scale_minus();
          break;
      case Qt::Key_Up:
          m_sampleOGLWidget->rotate_up();
          break;
      case Qt::Key_Down:
          m_sampleOGLWidget->rotate_down();
          break;
      case Qt::Key_Left:
          m_sampleOGLWidget->rotate_left();
          break;
      case Qt::Key_Right:
         m_sampleOGLWidget->rotate_right();
         break;
      case Qt::Key_Space:
         m_sampleOGLWidget->defaultScene();
         break;
   }
   m_sampleOGLWidget->update();
}
