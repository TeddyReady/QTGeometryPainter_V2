#include "rotdialog.h"
#include "ui_rotdialog.h"

RotDialog::RotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotDialog)
{
    ui->setupUi(this);
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setMinimum(-180);
    ui->horizontalSlider->setMaximum(180);
    ui->horizontalSlider->setSingleStep(1);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), parent, SLOT(update()));
}

RotDialog::~RotDialog()
{
    delete ui;
}

void RotDialog::on_horizontalSlider_valueChanged(int value)
{
    FigureManager::getManager().rotateSelected(value);
}

