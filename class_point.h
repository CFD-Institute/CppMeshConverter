#pragma once

#include <iostream>
#include <cmath>

using namespace std;

class point{

public:
    point(){};
    point(double, double, double, unsigned);
	bool operator==(point);
	void print();
	int get_ident();
	double get_x();
	double get_y();
	double get_z();

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

inline bool point::operator==(point rhs)
{
	if (abs(this->x - rhs.x) <= 1.0e-9 && abs(this->y - rhs.y) <= 1.0e-9 && abs(this->z - rhs.z) <= 1.0e-9)
	{
		return true;
	}
	return false;
}

inline int point::get_ident()
{
	return this->ident;
}

inline double point::get_x()
{
	return this->x;
}

inline double point::get_y()
{
	return this->y;
}

inline double point::get_z()
{
	return this->z;
}

void point::print()
{
    cout << this -> x << " " << this -> y << " " << this -> z << "\n" << endl;
}

