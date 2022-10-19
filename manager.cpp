#include "manager.h"

FigureManager::FigureManager() {}

void FigureManager::createFirstFigure(int ordX, int ordY, TypeOfFigures figureType) {

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
        break;

    case TypeOfFigures::second:
        figure.setBegin(figurePointRadius);

        figure.createRect(figurePitDeepth, E);
        figure.createWave(figurePointRadius, A);
        figure.createSquare(figurePointSlice, B);
        figure.createLine(B);
        figure.createWave(figurePointRadius, C);
        figure.createWave(figurePointRadius, D);
        break;

    case TypeOfFigures::none:
        return;

    default:
        return;
    }

    figures.push_back(figure);
}

void FigureManager::rotateFigure(size_t i, int rotationValue){
    if (i >= figures.size()) {
        return;
    }

    Figure selectedFigure = figures[i];

    if (qAbs(selectedFigure.getRotationValue() - rotationValue) < 0.01) {
        return;
    }

    QTransform transform;
    transform.translate(selectedFigure.getOrdX() + figureWidth / 2, selectedFigure.getOrdY() + figureHeight / 2);
    transform.rotate(rotationValue);
    transform.translate(-selectedFigure.getOrdX() - figureWidth / 2, -selectedFigure.getOrdY() - figureHeight / 2);

    figures[i].circuit = transform.map(selectedFigure.circuit);
    figures[i].rotationValue = rotationValue;
}

void FigureManager::rotateSelected(int rotationValue){
    if (qAbs(selected->rotationValue - rotationValue) < 0.01) {
        return;
    }

    QTransform transform;
    transform.translate(selected->getOrdX() + figureWidth / 2, selected->getOrdY() + figureHeight / 2);
    transform.rotate(rotationValue);
    transform.translate(-selected->getOrdX() - figureWidth / 2, -selected->getOrdY() - figureHeight / 2);

    selected->circuit = transform.map(selected->circuit);
    selected->rotationValue = rotationValue;
}

void FigureManager::chooseFigure(size_t i){
    if (i >= figures.size()) {
        return;
    }

    selected = &figures[i];
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

void FigureManager::changeSelectedFigure() {}

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

Figure*  FigureManager::getSelectedFigure(){ return selected; }
