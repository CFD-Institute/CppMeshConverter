#include <iostream>
#include <chrono>
#include "GmshReader.h"
#include "class_cell_2D.h"

using namespace std;
using namespace std::chrono;

int main()
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	list_cell_2D list_cell;

	list_cell.msh_reader.read_mesh();
	list_cell.msh_reader.construct_id_nodes();

	list_cell.assign_vextex();
	list_cell.assign_faces();
	list_cell.assign_boundary_condition();
	list_cell.detect_nearest_neighbor();
	list_cell.write_vtk();

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(t2 - t1).count();

	cout << duration << " seconds." << endl;

	//list_cell.calcul_vol_cells();

    return 0;
}
