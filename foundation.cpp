#include "foundation.h"

Foundation::Foundation(QWidget *parent) : QMainWindow(parent) {
    //Инициализируем действия меню
    quit = new QAction("&Exit..", this);
    destroyAllFigures = new QAction("&Clear field", this);
    destroyOnlyNoise = new QAction("&Clear crossing objects", this);

    //Установим горячие клавиши
    quit->setShortcut(tr("CTRL+Q"));
    destroyAllFigures->setShortcut(tr("CTRL+ALT+D"));
    destroyOnlyNoise->setShortcut(tr("CTRL+D"));

    //Создание меню:
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(destroyAllFigures);
    fileMenu->addAction(destroyOnlyNoise);
    fileMenu->addSeparator();
    fileMenu->addAction(quit);

    //Связываем Action'ы со слотами
    connect(quit, SIGNAL(triggered(bool)), this, SLOT(quitTask()));
    connect(destroyAllFigures, SIGNAL(triggered(bool)), this, SLOT(destroyAllTask()));
    connect(destroyOnlyNoise, SIGNAL(triggered(bool)), this, SLOT(destroyCrossingTask()));

    //Создаем панель инструментов
    toolbar = addToolBar("ToolBar");

    //Инициализируем Actions:
    appendAction = new QAction(QIcon(":/new/prefix1/icon/plus.png"),"Add Figure");
    type1Action = new QAction(QIcon(":/new/prefix1/icon/type1.png"),"Select Modify 1 of Figure");
    type2Action = new QAction(QIcon(":/new/prefix1/icon/type2.png"),"Select Modify 2 of Figure");
    destroyAction = new QAction(QIcon(":/new/prefix1/icon/trash.png"),"Destroy Object");

    //Установим горячие клавиши
    appendAction->setShortcut(tr("CTRL+A"));
    type1Action->setShortcut(tr("CTRL+1"));
    type2Action->setShortcut(tr("CTRL+2"));
    destroyAction->setShortcut(tr("DELETE"));

    //Устанавливаем типы Actions:
    appendAction->setDisabled(true);
    type1Action->setCheckable(true);
    type2Action->setCheckable(true);
    destroyAction->setDisabled(true);

    //Связывание соответсвующих сигналов Action со слотами:
    connect(appendAction, SIGNAL(triggered(bool)), this, SLOT(addFigureTask()));
    connect(type1Action, SIGNAL(triggered(bool)), this, SLOT(chooseFigureType1Task()));
    connect(type2Action, SIGNAL(triggered(bool)), this, SLOT(chooseFigureType2Task()));
    connect(destroyAction, SIGNAL(triggered(bool)), this, SLOT(destroyFigureTask()));

    //Добавление Action'ов на панель инструментов:
    toolbar->addAction(appendAction);
    toolbar->addSeparator();
    toolbar->addAction(type1Action);
    toolbar->addAction(type2Action);
    toolbar->addSeparator();
    toolbar->addAction(destroyAction);

    //Убираем выбор показа тулбара
    this->setContextMenuPolicy(Qt::NoContextMenu);

    //Установка белого фона:
    this->setStyleSheet("background-color:white;");
    menuBar()->setStyleSheet("QMenuBar { background-color: lightGray }");
    fileMenu->setStyleSheet("QMenu { background-color: lightGray }");
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

                QMenu *contextMenu = new QMenu();
                QAction *deleteAction = new QAction("Delete", this);
                QAction *editAction = new QAction("Edit...", this);
                QAction *rotateAction = new QAction("Rotate...", this);
                QAction *moveAction = new QAction("Move", this);

                connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(destroyFigureTask()));
                connect(editAction, SIGNAL(triggered(bool)), this, SLOT(editFigure(bool)));
                connect(rotateAction, SIGNAL(triggered(bool)), this, SLOT(rotateFigure(bool)));
                connect(moveAction, SIGNAL(triggered(bool)), this, SLOT(moveFigure(bool)));

                contextMenu->addAction(deleteAction);
                contextMenu->addAction(editAction);
                contextMenu->addAction(rotateAction);
                contextMenu->addAction(moveAction);

                contextMenu->popup(this->mapToGlobal(event->pos()));
            }

            found = true;
            break;
        }
    }

    if (!found) {
        if (event->button() == Qt::LeftButton) {
            FigureManager::getManager().removeSelection();
        }
    }
    this->update();
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

void Foundation::quitTask() { qApp->exit(); }
void Foundation::destroyAllTask() {
    FigureManager::getManager().figures.clear();
    statusBar()->showMessage("Figures removed");
    this->update();
}
void Foundation::destroyCrossingTask() {
    std::vector<int> figuresToDelete = std::vector<int>();

    for (size_t i = 0; i < FigureManager::getManager().figures.size(); i++) {
        for (size_t j = 0; j < FigureManager::getManager().figures.size(); j++) {
            if (i != j && FigureManager::getManager().figures[i].circuit.intersects(FigureManager::getManager().figures[j].circuit)) {
                if (std::find(figuresToDelete.begin(), figuresToDelete.end(), i) == figuresToDelete.end()) {
                    figuresToDelete.push_back(i);
                }
                if (std::find(figuresToDelete.begin(), figuresToDelete.end(), j) == figuresToDelete.end()) {
                    figuresToDelete.push_back(j);
                }
            }
        }
    }
    for (size_t i = 0; i < figuresToDelete.size(); i++) {
        FigureManager::getManager().removeFigure(figuresToDelete[i] - i);
    }
    statusBar()->showMessage("Intersections removed");
    this->update();
}

void Foundation::addFigureTask() {
    int randX, randY, randW, randH, randA;
    randX = 1 + (rand() % 1000);
    randY = 1 + (rand() % 700);
    randW = 250 + (rand() % 150);
    randH = 70 + (rand() % 180);
    randA = 0 + (rand() % 360);

    if (type1Action->isChecked()) {
        FigureManager::getManager().
                createFigure(randX, randY, randW, randH, randA, selectedType);
        statusBar()->showMessage("Figure added");
        this->update();
        return;
    }
    if (type2Action->isChecked()) {
        FigureManager::getManager().
                createFigure(randX, randY, randW, randH, randA, selectedType);
        statusBar()->showMessage("Figure added");
        this->update();
        return;
    }
}
void Foundation::chooseFigureType1Task() {
    if (type1Action->isChecked()) {
        type2Action->setChecked(false);
        appendAction->setEnabled(true);
        selectedType = TypeOfFigures::first;
    }
    else {
        appendAction->setEnabled(false);
        selectedType = TypeOfFigures::none;
    }
    statusBar()->showMessage("Type 1 selected");
}
void Foundation::chooseFigureType2Task() {
    if (type2Action->isChecked()) {
        type1Action->setChecked(false);
        appendAction->setEnabled(true);
        selectedType = TypeOfFigures::second;
    }
    else {
        appendAction->setEnabled(false);
        selectedType = TypeOfFigures::none;
    }
    statusBar()->showMessage("Type 2 selected");
}
void Foundation::destroyFigureTask() {
    FigureManager::getManager().removeSelectedFigure();
    this->update();
    statusBar()->showMessage("Figure destroyed");
}

void Foundation::editFigure(bool) {
    ChangeDialog *dialog = new ChangeDialog(this);
    dialog->show();
    statusBar()->showMessage("Figure edited");
    this->update();
}
void Foundation::moveFigure(bool)
{
    updateFrames = true;
    statusBar()->showMessage("Figure moved");
}
void Foundation::rotateFigure(bool) {
    RotDialog *rotDialog = new RotDialog(this);
    rotDialog->show();
    statusBar()->showMessage("Figure rotated");
    this->update();
}
