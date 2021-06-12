/* 
 * File:   Face.h
 * Author: HP
 *
 * Created on June 12, 2021, 4:08 PM
 */

#ifndef FACE_H
#define FACE_H
#include "Point.h"
class Face {
    
public:
    Face() {};
    
    void setP1(Point);
    void setP2(Point);
    void setCentroid(Point);
    void setBcTyp(int);
    void setIdFace(unsigned);
    void setArea(double);
    
    Point getP1();
    Point getP2();
    Point getCentroid();
    int getBcTyp();
    unsigned getIdFace();
    double getArea();
    
private:
    Point p1, p2;
    int bcTyp;
    unsigned idFace;
    double area = 0.0;
    Point centroid;
};

#endif /* FACE_H */

