#ifndef POINT_H
#define POINT_H
class Point {

public:
    Point(){};
    Point(double, double, double, unsigned);
    bool operator==(Point&) const;
    void print() const;
    unsigned getId() const;
    double getX() const;
    double getY() const;
    double getZ() const;
    Point* setId(unsigned);
    Point* setX(double);
    Point* setY(double);
    Point* setZ(double);

private:
    double x;
    double y;
    double z;
    unsigned ident;
};

#endif /* POINT_H */
