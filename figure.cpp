#include "figure.h"

Figure::Figure(int ordX, int ordY, int figureWidth, int figureHeight)
    : ordX(ordX), ordY(ordY), figureWidth(figureWidth), figureHeight(figureHeight) {}

void Figure::setBegin(int startPoint) {
    circuit.moveTo(ordX + startPoint, ordY);
}

void Figure::createLine(Sectors section, int endPoint) {
    switch (section) {

    case Sectors::A:
        circuit.lineTo(ordX + figureWidth, ordY + figureHeight - endPoint);
        break;

    case Sectors::B:
        circuit.lineTo(ordX + figureWidth / 2 + endPoint, ordY + figureHeight);
        break;

    case Sectors::C:
        circuit.lineTo(ordX, ordY + endPoint);
        break;

    case Sectors::D:
        circuit.lineTo(ordX + figureWidth / 2 - endPoint, ordY);
        break;

    case Sectors::E:
        circuit.lineTo(ordX + figureWidth - endPoint, ordY);
        break;

    case Sectors::F:
        circuit.lineTo(ordX + endPoint, ordY + figureHeight);
        break;

    default:
        break;
    }
}

void Figure::setLocation(int ordX, int ordY){
    prevOrdX = this->ordX;
    prevOrdY = this->ordY;
    this->ordX = ordX;
    this->ordY= ordY;
}

void Figure::recoveryLocation() {
    circuit.translate(prevOrdX - this->ordX, prevOrdY - this->ordY);
    this->ordX = prevOrdX;
    this->ordY = prevOrdY;
}

void Figure::createWave(double ray, Sectors section)
{
    figurePerimeter -= 2 * ray;
    figurePerimeter += M_PI_2 * ray;
    figureArea -= ray * ray;
    figureArea += M_PI_4 * ray * ray;

    switch (section) {
    case Sectors::D:
        createLine(Sectors::D, ray);
        circuit.arcTo(ordX, ordY, ray * 2, ray * 2, 180, -90);
        break;

    case Sectors::A:
        createLine(Sectors::A, ray);
        circuit.arcTo(ordX + figureWidth - ray * 2, ordY, ray * 2, ray * 2, 90, -90);
        break;

    case Sectors::C:
        createLine(Sectors::C, ray);
        circuit.arcTo(ordX, ordY + figureHeight - ray * 2, ray * 2, ray * 2, -90, -90);
        break;

    case Sectors::B:
        createLine(Sectors::A, ray);
        circuit.arcTo(ordX + figureWidth - ray * 2, ordY + figureHeight - ray * 2, ray * 2, ray * 2, 0, -90);
        break;

    default:
        break;
    }
}

void Figure::createCone(double ray, Sectors section)
{
    figurePerimeter -= 2 * ray;
    figurePerimeter += M_PI_2 * ray;
    figureArea -= M_PI_4 * ray * ray;

    switch (section) {
    case Sectors::D:
        createLine(Sectors::C, ray);
        circuit.arcTo(ordX - ray, ordY - ray, ray * 2, ray * 2, 270, 90);
        break;

    case Sectors::A:
        createLine(Sectors::E, ray);
        circuit.arcTo(ordX + figureWidth - ray, ordY - ray, ray * 2, ray * 2, 180, 90);
        break;

    case Sectors::C:
        createLine(Sectors::F, ray);
        circuit.arcTo(ordX - ray, ordY + figureHeight - ray, ray * 2, ray * 2, 0, 90);
        break;

    case Sectors::B:
        createLine(Sectors::A, ray);
        circuit.arcTo(ordX + figureWidth - ray, ordY + figureHeight - ray, ray * 2, ray * 2, 90, 90);
        break;

    default:
        break;
    }
}

void Figure::createSphere(double ray, Sectors section)
{
    figurePerimeter -= 2 * ray;
    figurePerimeter += M_PI * ray;
    figureArea -= M_PI_2 * ray * ray;

    switch (section) {
    case Sectors::E:
        createLine(Sectors::D, ray);
        circuit.arcTo(ordX + figureWidth / 2 - ray, ordY - ray, ray * 2, ray * 2, 180, 180);
        break;

    case Sectors::F:
        createLine(Sectors::B, ray);
        circuit.arcTo(ordX + figureWidth / 2 - ray, ordY + figureHeight - ray, ray * 2, ray * 2, 0, 180);
        break;

    default:
        break;
    }
}

void Figure::createSquare(double length, Sectors section)
{
    figureArea -= length * length;

    switch (section) {
    case Sectors::D:
        createLine(Sectors::C, length);
        circuit.lineTo(ordX + length, ordY + length);
        circuit.lineTo(ordX + length, ordY);
        break;

    case Sectors::A:
        createLine(Sectors::E, length);
        circuit.lineTo(ordX + figureWidth - length, ordY + length);
        circuit.lineTo(ordX + figureWidth, ordY + length);
        break;

    case Sectors::C:
        createLine(Sectors::F, length);
        circuit.lineTo(ordX + length, ordY + figureHeight - length);
        circuit.lineTo(ordX, ordY + figureHeight - length);
        break;

    case Sectors::B:
        createLine(Sectors::A, length);
        circuit.lineTo(ordX + figureWidth - length, ordY + figureHeight - length);
        circuit.lineTo(ordX + figureWidth - length, ordY + figureHeight);
        break;

    default:
        break;
    }
}

void Figure::createTriangle(double length, Sectors section)
{

    figurePerimeter -= length * 2;
    figurePerimeter += length * M_SQRT2;
    figureArea -= length * length * 0.5;

    switch (section) {
    case Sectors::D:
        createLine(Sectors::C, length);
        circuit.lineTo(ordX + length, ordY);
        break;

    case Sectors::A:
        createLine(Sectors::E, length);
        circuit.lineTo(ordX + figureWidth, ordY + length);
        break;

    case Sectors::C:
        createLine(Sectors::F, length);
        circuit.lineTo(ordX, ordY + figureHeight - length);
        break;

    case Sectors::B:
        createLine(Sectors::A, length);
        circuit.lineTo(ordX + figureWidth - length, ordY + figureHeight);
        break;

    default:
        break;
    }
}

void Figure::createRect(double length, Sectors section)
{
    figurePerimeter += 2 * length;
    figureArea -= 2 * length * length;

    switch (section) {
    case Sectors::E:
        createLine(Sectors::D, length);
        circuit.lineTo(ordX + figureWidth / 2 - length, ordY + length);
        circuit.lineTo(ordX + figureWidth / 2 + length, ordY + length);
        circuit.lineTo(ordX + figureWidth / 2 + length, ordY);
        break;

    case Sectors::F:
        createLine(Sectors::B, length);
        circuit.lineTo(ordX + figureWidth / 2 + length, ordY + figureHeight - length);
        circuit.lineTo(ordX + figureWidth / 2 - length, ordY + figureHeight - length);
        circuit.lineTo(ordX + figureWidth / 2 - length, ordY + figureHeight);
        break;

    default:
        break;
    }
}

int Figure::getOrdX() { return ordX; }
int Figure::getOrdY() { return ordY; }
int Figure::getRotationValue() { return rotationValue; }
int Figure::getFigureHeight() { return figureHeight; }
int Figure::getFigureWidth() { return figureWidth; }
double Figure::getFigurePerimeter() { return figurePerimeter; }
double Figure::getFigureArea() { return figureArea; }
