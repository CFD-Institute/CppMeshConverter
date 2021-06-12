
#include "Face.h"

void Face::setP1(Point p1) {
    this->p1 = p1;
}

Point Face::getP1() {
    return this->p1;
}

void Face::setP2(Point p2) {
    this->p2 = p2;
}

Point Face::getP2() {
    return this->p2;
}

void Face::setCentroid(Point centroid) {
    this->centroid = centroid;
}

Point Face::getCentroid() {
    return this->centroid;
}

void Face::setBcTyp(int bcTyp) {
    this->bcTyp = bcTyp;
}

int Face::getBcTyp() {
    return this->bcTyp;
}

void Face::setIdFace(unsigned idFace) {
    this->idFace = idFace;
}

unsigned Face::getIdFace() {
    return this->idFace;
}

void Face::setArea(double area) {
    this->area = area;
}

double Face::getArea() {
    return this->area;
}