#pragma once
#include "class_point.h"


unsigned nbfaces;

struct face {
	point p1, p2;
	int bc_typ;
	unsigned idface;
	double area = 0.0;
	point centroid;
};

class cell_2D : public point {

public:
	unsigned ident = 0;
	point vertex[4];
	face faces[4];
	cell_2D *neighbor1 = nullptr;
	cell_2D *neighbor2 = nullptr;
	cell_2D *neighbor3 = nullptr;
	cell_2D *neighbor4 = nullptr;
	double vol = 0.0;

	void assign_vertex(unsigned);
};

void cell_2D::assign_vertex(unsigned i)
{
	this->ident = i;

}