#include "changedialog.h"
#include "ui_changedialog.h"
#include <iostream>

ChangeDialog::ChangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeDialog)
{
    ui->setupUi(this);
    Figure *selectedFigure = FigureManager::getManager().getSelectedFigure();
    ui->heightEdit->setText(QString::number(selectedFigure->getFigureHeight()));
    ui->widthEdit->setText(QString::number(selectedFigure->getFigureWidth()));
    ui->xEdit->setText(QString::number(selectedFigure->getOrdX()));
    ui->yEdit->setText(QString::number(selectedFigure->getOrdY()));
    ui->rotationEdit->setText(QString::number(selectedFigure->getRotationValue()));
    ui->areaOutput->setText(QString::number(selectedFigure->getFigureArea()));
    ui->perimeterOutput->setText(QString::number(selectedFigure->getFigurePerimeter()));
}

ChangeDialog::~ChangeDialog()
{
    delete ui;
}

void ChangeDialog::on_submitDialogBox_accepted()
{
    int width = qStringToDouble(ui->widthEdit->text());
    int height = qStringToDouble(ui->heightEdit->text());
    int angle = qStringToDouble(ui->rotationEdit->text());
    int x = qStringToDouble(ui->xEdit->text());
    int y = qStringToDouble(ui->yEdit->text());

    TypeOfFigures figureType = FigureManager::getManager().getSelectedFigure()->getTypeOfFigure();
    FigureManager::getManager().removeSelectedFigure();
    FigureManager::getManager().createFirstFigure(x, y, width, height, angle, figureType);
}

double ChangeDialog::qStringToDouble(const QString &value)
{
    double result;
    if (value.isEmpty())
        result = std::numeric_limits<double>::quiet_NaN();
    else
        result = value.toDouble();
    return result;
}
