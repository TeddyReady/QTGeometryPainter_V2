#pragma once
#include <QtGui>
#include <QtCore>

enum Sectors {A, B, C, D, E, F};

class Figure {
private:
    //Координаты
    int ordX;
    int prevOrdX;
    int ordY;
    int prevOrdY;
    //Данные фигуры
    int figureWidth;
    int figureHeight;
    double figureArea;
    double figurePerimeter;

public:
    Figure(int ordX, int ordY, int figureWidth, int figureHeight);

    QPainterPath circuit;
    int rotationValue;

    //Координатные методы
    void setBegin(int startPoint);
    void createLine(Sectors section, int endPoint = 0);
    void setLocation(int ordX, int ordY);
    void recoveryLocation();

    //Создание фигурных модификаций
    void createWave(double ray, Sectors section);
    void createCone(double ray, Sectors section);
    void createSphere(double ray, Sectors section);
    void createSquare(double length, Sectors section);
    void createTriangle(double length, Sectors section);
    void createRect(double length, Sectors section);

    //Геттеры полей Фигуры
    int getOrdX();
    int getOrdY();
    int getRotationValue();
    int getFigureHeight();
    int getFigureWidth();
    double getFigurePerimeter();
    double getFigureArea();
};
