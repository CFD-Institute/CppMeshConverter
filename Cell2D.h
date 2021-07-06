/* 
 * File:   Cell2D.h
 * Author: HP
 *
 * Created on June 12, 2021, 4:01 PM
 */

#pragma once
#include "Face.h"
#include <array>

class Cell2D {
public:
    Cell2D() {};
    unsigned getIdent() const;
    Point& getVertex1();
    Point& getVertex2();
    Point& getVertex3();
    Point& getVertex4();
    Face& getFace1();
    Face& getFace2();
    Face& getFace3();
    Face& getFace4();
    Cell2D* getNeighbor1();
    Cell2D* getNeighbor2();
    Cell2D* getNeighbor3();
    Cell2D* getNeighbor4();
    double getVol() const;
    
    void setIdent(unsigned);
    void setVertex(Point*);
    void setVertex1(Point);
    void setVertex2(Point);
    void setVertex3(Point);
    void setVertex4(Point);
    void setFace(Face*);
    void setNeighbor1(Cell2D*);
    void setNeighbor2(Cell2D*);
    void setNeighbor3(Cell2D*);
    void setNeighbor4(Cell2D*);
    void setVol(double);

    const std::array<Point, 4>& getVertices() const;

    const std::array<Face, 4>& getFaces() const;

  private:
    unsigned ident = 0;
    std::array<Point, 4> vertices;
    std::array<Face, 4> faces;
    Cell2D *neighbor1 = nullptr;
    Cell2D *neighbor2 = nullptr;
    Cell2D *neighbor3 = nullptr;
    Cell2D *neighbor4 = nullptr;
    double vol = 0.0;   
};
