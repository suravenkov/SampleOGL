#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SampleOGLWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent* keyEvent) override;
private slots:
    void on_pushButton_Color_clicked();
    void on_pushButton_xRotate_clicked();
    void on_pushButton_yRotate_clicked();
    void on_pushButton_zRotate_clicked();
    void on_pushButton_FreeRotate_clicked();

    void on_pushButton_help_clicked();

private:
    SampleOGLWidget* m_sampleOGLWidget;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
