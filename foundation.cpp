#include "foundation.h"
#include "manager.h"
#include "ui_foundation.h"

Foundation::Foundation(QWidget *parent) : QMainWindow(parent) {
    //Установка белого фона:
    this->setStyleSheet("background-color:white;");

    //Создание меню:
    quit = new QAction("&Quit", this);
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(quit);
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);

    //Создаем панель инструментов
    toolbar = addToolBar("ToolBar");

    //Инициализируем Actions:
    appendAction = new QAction(QIcon(":/new/prefix1/icon/plus.png"),"Add Figure");
    type1Action = new QAction(QIcon(":/new/prefix1/icon/type1.png"),"Select Modify 1 of Figure");
    type2Action = new QAction(QIcon(":/new/prefix1/icon/type2.png"),"Select Modify 2 of Figure");
    destroyAction = new QAction(QIcon(":/new/prefix1/icon/trash.png"),"Destroy Object");

    //Устанавлваем типы Actions:
    appendAction->setDisabled(true);
    type1Action->setCheckable(true);
    type2Action->setCheckable(true);
    destroyAction->setDisabled(true);

    //Связывание соответсвующих сигналов Action со слотами:
    connect(appendAction, SIGNAL(triggered(bool)), this, SLOT(addFigureTask()));
    connect(type1Action, SIGNAL(triggered(bool)), this, SLOT(chooseFigureType1Task()));
    connect(type2Action, SIGNAL(triggered(bool)), this, SLOT(chooseFigureType2Task()));
    connect(destroyAction, SIGNAL(triggered(bool)), this, SLOT(destroyFigureTask()));

    //Запрет перемещения:
    toolbar->setMovable(false);

    //Добавление Action'ов на панель инструментов:
    toolbar->addAction(appendAction);
    toolbar->addSeparator();
    toolbar->addAction(type1Action);
    toolbar->addAction(type2Action);
    toolbar->addSeparator();
    toolbar->addAction(destroyAction);
}

void Foundation::moveFigureToCursor()
{
    QPoint cursorLocation = this->mapFromGlobal(QCursor::pos());

    try {
        FigureManager::getManager().moveSelectedToCoordinates(cursorLocation.x(), cursorLocation.y(), this->size().width(), this->size().height());
    }
    catch (std::out_of_range & e) {
        statusBar()->showMessage("Out of bounds");
        setMouseTracking(false);
        canMoveObjects = false;
        updateFrames = false;
    }
}

void Foundation::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    FigureManager::getManager().renderFigures(painter);

    if (FigureManager::getManager().isSelectedFiguresOnWindow()) {
        destroyAction->setEnabled(true);
    }
    else {
        destroyAction->setEnabled(false);
    }

    if (updateFrames) {
        moveFigureToCursor();
        this->update();
    }
}

void Foundation::mousePressEvent(QMouseEvent *event) {
    QPainterPath mouseRect;
    mouseRect.addRect(event->pos().x(), event->pos().y(), 1, 1);

    bool found = false;
    updateFrames = false;

    for (auto &figure : FigureManager::getManager().figures) {
        if (figure.circuit.intersects(mouseRect)) {

            if (event->button() == Qt::LeftButton) {
                FigureManager::getManager().chooseFigure(&figure);
                destroyAction->setEnabled(true);
                setMouseTracking(true);
            }
            else if (event->button() == Qt::RightButton) {
                FigureManager::getManager().chooseFigure(&figure);
                destroyAction->setEnabled(true);

                QMenu * contextMenu = new QMenu();
                QAction * deleteAction = new QAction("Delete", this);
                QAction * editAction = new QAction("Edit", this);
                QAction * rotateAction = new QAction("Rotate", this);

                connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(deleteFigure(bool)));
                //connect(editAction, SIGNAL(triggered(bool)), this, SLOT(editFigure(bool)));
                //connect(rotateAction, SIGNAL(triggered(bool)), this, SLOT(rotateFigure(bool)));

                contextMenu->addAction(deleteAction);
                contextMenu->addAction(editAction);
                contextMenu->addAction(rotateAction);

                contextMenu->popup(this->mapToGlobal(event->pos()));
            }

            found = true;
            break;
        }
        this->repaint();
    }

    if (!found) {
        if (event->button() == Qt::LeftButton) {
            FigureManager::getManager().removeSelection();
        }
    }
}

void Foundation::mouseMoveEvent(QMouseEvent *event) {
    if (!canMoveObjects) {
        return;
    }

    try {
        FigureManager::getManager().moveSelectedToCoordinates(event->pos().x(), event->pos().y(), this->size().width(), this->size().height());
    }
    catch (std::out_of_range & event) {
        statusBar()->showMessage("Out of bounds");
        setMouseTracking(false);
        canMoveObjects = false;
    }

    this->update();
}

void Foundation::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    setMouseTracking(false);
    canMoveObjects = true;
}

void Foundation::addFigureTask() {
    FigureManager::getManager().
            createFirstFigure(50, 50, selectedType);
    this->update();
    appendAction->setDisabled(true);
    if (type1Action->isChecked()) {
        type1Action->setChecked(false);
        return;
    }
    if (type2Action->isChecked()) {
        type2Action->setChecked(false);
        return;
    }
}

void Foundation::chooseFigureType1Task() {
    if (type1Action->isCheckable()) {
        type2Action->setChecked(false);
        appendAction->setEnabled(true);
        selectedType = TypeOfFigures::first;
    }
    else {
        selectedType = TypeOfFigures::none;
    }
}

void Foundation::chooseFigureType2Task() {
    if (type2Action->isCheckable()) {
        type1Action->setChecked(false);
        appendAction->setEnabled(true);
        selectedType = TypeOfFigures::second;
    }
    else {
        selectedType = TypeOfFigures::none;
    }
}

void Foundation::fitFiguresTask() {}

void Foundation::destroyFigureTask() {
    FigureManager::getManager().removeSelectedFigure();
    this->update();
}

void Foundation::deleteFigure(bool)
{
    FigureManager::getManager().removeSelectedFigure();
    this->update();
}

/*void Foundation::editFigure(bool)
{
    EditShapeDialog * editShapeDialog = new EditShapeDialog(this);
    editShapeDialog->show();
    this->update();
}*/

/*void Foundation::rotateFigure(bool)
{
    RotateShapeDialog * rotateDialog = new RotateShapeDialog(this);
    rotateDialog->show();
    this->update();
}*/
