#include "changedialog.h"
#include "ui_changedialog.h"
#include <iostream>

ChangeDialog::ChangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeDialog)
{
    ui->setupUi(this);

    //Устанавоиваем текущие параметры в окно
    Figure *selectedFigure = FigureManager::getManager().getSelectedFigure();
    ui->heightEdit->setText(QString::number(selectedFigure->getFigureHeight()));
    ui->widthEdit->setText(QString::number(selectedFigure->getFigureWidth()));
    ui->xEdit->setText(QString::number(selectedFigure->getOrdX()));
    ui->yEdit->setText(QString::number(selectedFigure->getOrdY()));
    ui->rotationEdit->setText(QString::number(selectedFigure->rotationValue));
    ui->areaOutput->setText(QString::number(selectedFigure->getFigureArea()));
    ui->perimeterOutput->setText(QString::number(selectedFigure->getFigurePerimeter()));
}

ChangeDialog::~ChangeDialog()
{
    delete ui;
}

void ChangeDialog::on_submitDialogBox_accepted()
{
    //Забираем значения из окна
    int localWidth = qStringToDouble(ui->widthEdit->text());
    int localHeight = qStringToDouble(ui->heightEdit->text());
    int localAngle = qStringToDouble(ui->rotationEdit->text());
    int localX = qStringToDouble(ui->xEdit->text());
    int localY = qStringToDouble(ui->yEdit->text());
    TypeOfFigures localType = FigureManager::getManager().getSelectedFigure()->getTypeOfFigure();

    //Удаляем старую и создаем новую фигуры
    FigureManager::getManager().removeSelectedFigure();
    FigureManager::getManager().createFigure(localX, localY, localWidth, localHeight, localAngle, localType);
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
