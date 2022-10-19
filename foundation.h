#pragma once
#include <QMainWindow>
#include <QApplication>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <algorithm>

#include "manager.h"
#include "changedialog.h"
#include "rotdialog.h"

class Foundation : public QMainWindow {
  Q_OBJECT
public:
    TypeOfFigures selectedType = TypeOfFigures::none;
private:
    //Меню
    QMenu *fileMenu;
    QAction *quit;
    QAction *destroyAllFigures;
    QAction *destroyOnlyNoise;

    //Панель инструментов
    QToolBar *toolbar;
    QAction *appendAction;
    QAction *type1Action;
    QAction *type2Action;
    QAction *destroyAction;

    //Переменные состояний
    bool canMoveObjects = true;
    bool updateFrames = false;

    //Перемещение фигуры за курсором
    void moveFigureToCursor();
public:
    Foundation(QWidget *parent = nullptr);

protected:
    //Эвенты
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    //Слоты Меню
    void quitTask();
    void destroyAllTask();
    void destroyCrossingTask();

    //Слоты Тулбара
    void addFigureTask();
    void chooseFigureType1Task();
    void chooseFigureType2Task();
    void destroyFigureTask();

    //Слоты SubМеню
    void editFigure(bool);
    void moveFigure(bool);
    void rotateFigure(bool);
};
