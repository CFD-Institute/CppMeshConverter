
#include "Cell2D.h"

unsigned Cell2D::getIdent() const {
    return this->ident;
}

Point& Cell2D::getVertex1()  {
    return vertices[0];
}

Point& Cell2D::getVertex2()  {
    return vertices[1];
}

Point& Cell2D::getVertex3()  {
    return vertices[2];
}

Point& Cell2D::getVertex4()  {
    return vertices[3];
}

Face& Cell2D::getFace1()  {
    return faces[0];
}

Face& Cell2D::getFace2()  {
    return faces[1];
}

Face& Cell2D::getFace3()  {
    return faces[2];
}

Face& Cell2D::getFace4()  {
    return faces[3];
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

double Cell2D::getVol() const {
    double x1 = vertices[0].getX();
    double x2 = vertices[1].getX();
    double x3 = vertices[2].getX();
    double x4 = vertices[3].getX();

    double y1 = vertices[0].getY();
    double y2 = vertices[1].getY();
    double y3 = vertices[2].getY();
    double y4 = vertices[3].getY();

    double vol = 0.5 * ((x1 - x3)*(y2 - y4) + (x4 - x2)*(y1 - y3));
    return vol;
}

void Cell2D::setIdent(unsigned ident) {
    this->ident = ident;
}

void Cell2D::setVertex1(Point p) {
    vertices[0] = p;
}

void Cell2D::setVertex2(Point p) {
    vertices[1] = p;
}

void Cell2D::setVertex3(Point p) {
    vertices[2] = p;
}

void Cell2D::setVertex4(Point p) {
    vertices[3] = p;
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

const std::array<Point, 4>& Cell2D::getVertices() const
{
  return vertices;
}

const std::array<Face, 4>& Cell2D::getFaces() const
{
  return faces;
}
