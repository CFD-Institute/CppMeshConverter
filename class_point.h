#ifndef CLASS_POINT_H_INCLUDED
#define CLASS_POINT_H_INCLUDED

#include <iostream>

using namespace std;

class point{

public:
    void print();
    point(){};
    point(double, double, double, unsigned);

private:
    double x;
    double y;
    double z;
    unsigned ident;
};

point::point(double x, double y, double z, unsigned ident)
{
    this -> x     = x;
    this -> y     = y;
    this -> z     = z;
    this -> ident = ident;
}

void point::print()
{
    cout << this -> x << " " << this -> y << " " << this -> z << "\n" << endl;
}

#endif // CLASS_POINT_H_INCLUDED
