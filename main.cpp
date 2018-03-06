#pragma once
#include <iostream>
#include "class_read_gmsh.h"
#include "class_cell_2D.h"

using namespace std;

int main()
{
	list_cell_2D list_cell;

	list_cell.msh_reader.read_mesh();
	list_cell.msh_reader.construct_id_nodes();

	list_cell.assign_vextex();
	list_cell.assign_faces();

    return 0;
}
