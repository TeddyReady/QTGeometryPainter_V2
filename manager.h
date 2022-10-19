#pragma once
#include <iostream>
#include <stdexcept>
#include <QtWidgets>
#include "figure.h"

enum TypeOfFigures { none, first, second };

//Реализуем паттерн "Одиночка"
//для Менеджера Фигур
class FigureManager {
private:
    FigureManager();
    FigureManager( const FigureManager&);
    FigureManager& operator=( FigureManager& );

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
    void createFirstFigure(int ordX, int ordY, TypeOfFigures figureType);

    //Поворот фигуры
    void rotateFigure(size_t i, int rotationValue);
    void rotateSelected(int rotationValue);

    //Выделение фигуры
    void chooseFigure(size_t i);
    void chooseFigure(Figure *figure);

    //Снятие выделения
    void removeSelection();

    //Удаление фигур
    void removeFigure(Figure *figure);
    void removeFigure(size_t i);
    void removeSelectedFigure();

    //Изменение выделенной фигуры
    void changeSelectedFigure();

    //Отрисовка фигур
    void renderFigures(QPainter &painter);

    //Перемещение фигуры по заданным координатам
    void moveSelectedToCoordinates(int ordX, int ordY, double winWidth, double winHeight);

    //Есть ли выбранные фигуры
    bool isSelectedFiguresOnWindow();

    //Геттер выбранной фигуры
    Figure *getSelectedFigure();
};
