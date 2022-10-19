#ifndef RotDialog_H
#define RotDialog_H

#include <QDialog>

#include "manager.h"

namespace Ui {
class RotDialog;
}

class RotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RotDialog(QWidget *parent = nullptr);
    ~RotDialog();

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::RotDialog *ui;
};

#endif // RotDialog_H
