
#include "Cell2D.h"

unsigned Cell2D::getIdent() {
    return this->ident;
}

Point* Cell2D::getVertex() {
    return this->vertex;
}

Face* Cell2D::getFace() {
    return this->faces;
}

Cell2D* Cell2D::getNeighbor1() {
    return neighbor1;
}

Cell2D* Cell2D::getNeighbor2() {
    return neighbor2;
}

Cell2D* Cell2D::getNeighbor3() {
    return neighbor3;
}

Cell2D* Cell2D::getNeighbor4() {
    return neighbor4;
}

double Cell2D::getVol() {
    double x1 = this->vertex[0].getX();
    double x2 = this->vertex[1].getX();
    double x3 = this->vertex[2].getX();
    double x4 = this->vertex[3].getX();

    double y1 = this->vertex[0].getY();
    double y2 = this->vertex[1].getY();
    double y3 = this->vertex[2].getY();
    double y4 = this->vertex[3].getY();

    double vol = 0.5 * ((x1 - x3)*(y2 - y4) + (x4 - x2)*(y1 - y3));
    return vol;
}

void Cell2D::setIdent(unsigned ident) {
    this->ident = ident;
}

void Cell2D::setVertex1(Point p) {
    this->vertex[0] = p;
}

void Cell2D::setVertex2(Point p) {
    this->vertex[1] = p;
}

void Cell2D::setVertex3(Point p) {
    this->vertex[2] = p;
}

void Cell2D::setVertex4(Point p) {
    this->vertex[3] = p;
}

void Cell2D::setNeighbor1(Cell2D* currentCell) {
    this->neighbor1 = currentCell;
}

void Cell2D::setNeighbor2(Cell2D* currentCell) {
    this->neighbor2 = currentCell;
}

void Cell2D::setNeighbor3(Cell2D* currentCell) {
    this->neighbor3 = currentCell;
}

void Cell2D::setNeighbor4(Cell2D* currentCell) {
    this->neighbor4 = currentCell;
}

void Cell2D::setVol(double vol) {
    this->vol = vol;
}
