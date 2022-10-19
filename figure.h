#pragma once
#include <QtGui>
#include <QtCore>

enum Sectors {A, B, C, D, E, F};
enum TypeOfFigures { none, first, second };

class Figure {
public:
    //Контур фигуры
    QPainterPath circuit;

    //Угол поворота
    int rotationValue;
private:
    //Координаты
    int ordX;
    int prevOrdX;
    int ordY;
    int prevOrdY;
    //Данные фигуры
    TypeOfFigures figureType;
    int figureWidth;
    int figureHeight;
    int figureArea;
    int figurePerimeter;

public:
    Figure(int ordX, int ordY, int figureWidth, int figureHeight, TypeOfFigures figureType);

    //Координатные методы
    void setBegin(int startPoint);
    void setLocation(int ordX, int ordY);
    void recoveryLocation();

    //Отрисовка фигурных модификаций
    void createLine(Sectors section, int endPoint = 0);
    void createWave(double ray, Sectors section);
    void createCone(double ray, Sectors section);
    void createSphere(double ray, Sectors section);
    void createSquare(double length, Sectors section);
    void createTriangle(double length, Sectors section);
    void createRect(double length, Sectors section);

    //Повороты фигуры
    void rotate(double rotValue);
    void resetRotation();

    //Геттеры полей Фигуры
    TypeOfFigures getTypeOfFigure();
    int getOrdX();
    int getOrdY();
    int getFigureWidth();
    int getFigureHeight();
    double getFigurePerimeter();
    double getFigureArea();
};
