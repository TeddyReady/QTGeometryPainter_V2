#include "manager.h"

FigureManager::FigureManager() {}

void FigureManager::createFigure(int ordX, int ordY, int width, int height, int angle,  TypeOfFigures figureType) {
    figureWidth = width;
    figureHeight = height;
    figurePointRadius = 10 + (rand() % 40);
    figurePointSlice = 10 + (rand() % 40);
    figurePitDeepth = 10 + (rand() % 40);
    figurePitRadius = 10 + (rand() % 40);
    Figure figure = Figure(ordX, ordY, figureWidth, figureHeight);

    switch (figureType) {
    case TypeOfFigures::first:
        figure.setBegin(figurePointRadius);

        figure.createSphere(figurePitRadius, E);
        figure.createLine(E);
        figure.createWave(figurePointRadius, B);
        figure.createRect(figurePitDeepth, F);
        figure.createTriangle(figurePointSlice, C);
        figure.createWave(figurePointRadius, D);

        figure.rotate(angle);
        break;

    case TypeOfFigures::second:
        figure.setBegin(figurePointRadius);

        figure.createRect(figurePitDeepth, E);
        figure.createWave(figurePointRadius, A);
        figure.createSquare(figurePointSlice, B);
        figure.createLine(B);
        figure.createWave(figurePointRadius, C);
        figure.createWave(figurePointRadius, D);

        figure.rotate(angle);
        break;

    case TypeOfFigures::none:
        return;

    default:
        return;
    }

    figures.push_back(figure);
}

void FigureManager::chooseFigure(Figure *figure){ selected = figure; }

void FigureManager::removeSelection(){ selected = nullptr; }

void FigureManager::removeFigure(Figure *figure) {
    for (size_t i = 0; i < figures.size(); i++) {
        if (figure == &figures[i]) {
            if (figure == selected) {
                selected = nullptr;
            }
            figures.erase(figures.begin() + i);
            break;
        }
    }
}

void FigureManager::removeFigure(size_t i) { figures.erase(figures.begin() + i); }

void FigureManager::removeSelectedFigure() {
    removeFigure(selected);
    removeSelection();
}

void FigureManager::renderFigures(QPainter & painter){
    for (Figure &figure : figures) {
        if (&figure == selected) {
            painter.strokePath(figure.circuit, QPen(Qt::blue, 4));
            continue;
        }
        painter.strokePath(figure.circuit, QPen(Qt::black, 2));
    }
}

void FigureManager::moveSelectedToCoordinates(int ordX, int ordY, double winWidth, double winHeight){
    if (selected == nullptr) {
        return;
    }

    QPainterPath window;
    window.addRect(0, 0, winWidth, winHeight);

    if (window.contains(selected->circuit)) {
        selected->circuit.translate(ordX - selected->getOrdX(), ordY - selected->getOrdY());
        selected->setLocation(ordX, ordY);
    }
    else {
        selected->recoveryLocation();
        throw std::out_of_range("The figure has fallen beyond the rendering boundary!");
    }
}

bool  FigureManager::isSelectedFiguresOnWindow(){ return selected != nullptr; }

Figure* FigureManager::getSelectedFigure(){ return selected; }
