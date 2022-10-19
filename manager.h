#pragma once
#include <iostream>
#include <stdexcept>
#include <QtWidgets>
#include <random>
#include "figure.h"

//Реализуем паттерн "Одиночка"
//для Менеджера Фигур
class FigureManager {
private:
    FigureManager();
    FigureManager(const FigureManager&);
    FigureManager& operator=(FigureManager&);

    Figure *selected = nullptr;
public:
    static FigureManager& getManager() {
        static FigureManager manager;
        return manager;
    }

    int figureWidth = 300;
    int figureHeight = 200;
    int figurePointRadius = 15;
    int figurePointSlice = 20;
    int figurePitDeepth = 20;
    int figurePitRadius = 20;

    std::vector<Figure> figures = std::vector<Figure>();
    //Создание первой фигуры
    void createFigure(int ordX, int ordY, int width, int height, int angle, TypeOfFigures figureType);

    //Выделение фигуры
    void chooseFigure(Figure *figure);

    //Снятие выделения
    void removeSelection();

    //Удаление фигур
    void removeFigure(Figure *figure);
    void removeFigure(size_t i);
    void removeSelectedFigure();

    //Отрисовка фигур
    void renderFigures(QPainter &painter);

    //Перемещение фигуры по заданным координатам
    void moveSelectedToCoordinates(int ordX, int ordY, double winWidth, double winHeight);

    //Есть ли выделенные фигуры в окне
    bool isSelectedFiguresOnWindow();

    //Получение выделенной фигуры
    Figure* getSelectedFigure();
};
