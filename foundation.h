#pragma once
#include <QMainWindow>
#include <QApplication>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "manager.h"


class Foundation : public QMainWindow {
  Q_OBJECT
private:
    //Меню
    QMenu *fileMenu;
    QAction *quit;
    //Панель инструментов
    QToolBar *toolbar;
    QAction *appendAction;
    QAction *type1Action;
    QAction *type2Action;
    QAction *fitAction;
    QAction *destroyAction;

    bool canMoveObjects = true;
    bool updateFrames = false;

    void moveFigureToCursor();
public:
    Foundation(QWidget *parent = nullptr);
    TypeOfFigures selectedType = TypeOfFigures::none;

protected:
    //Эвенты
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    //Слоты
    void addFigureTask();
    void chooseFigureType1Task();
    void chooseFigureType2Task();
    void fitFiguresTask();
    void destroyFigureTask();

    void deleteFigure(bool);
    //void editFigure(bool);
    //void rotateFigure(bool);
};
