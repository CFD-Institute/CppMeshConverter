#pragma once
#include <vector>
#include "class_point.h"


unsigned nbfaces;

struct face {
	point p1, p2;
	int bc_typ;
	unsigned idface;
	double area = 0.0;
	point centroid;
};

struct cell_2D : public point {
	unsigned ident = 0;
	point vertex[4];
	face faces[4];
	cell_2D *neighbor1 = nullptr;
	cell_2D *neighbor2 = nullptr;
	cell_2D *neighbor3 = nullptr;
	cell_2D *neighbor4 = nullptr;
	double vol = 0.0;
};

class list_cell_2D : public cell_2D {

public:
	GmshReader msh_reader;
	vector<cell_2D> cells;
	void assign_vextex();
};

void list_cell_2D::assign_vextex()
{
	for (unsigned i = 0; i < msh_reader.nbelm; i++) {
		this->cells[i].ident = i + 1;
		int idnode = msh_reader.coord_nodes[i].get_ident();

		for (unsigned j = 0; j < msh_reader.nbnode; j++)
		{
			if (idnode == msh_reader.coord_nodes[j].get_ident())
			{
				//this->cells[i].vertex[0] = 
			}
		}
	}
}