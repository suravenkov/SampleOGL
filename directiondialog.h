#ifndef DIRECTIONDIALOG_H
#define DIRECTIONDIALOG_H

#include <QDialog>
#include <QVector3D>

namespace Ui {
class DirectionDialog;
}

class DirectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DirectionDialog(QWidget *parent = nullptr);
    ~DirectionDialog();

    QVector3D direction() const;
    void setDirection(const QVector3D& direction) const;

private:
    Ui::DirectionDialog *ui;
};

#endif // DIRECTIONDIALOG_H
