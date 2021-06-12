#include <iostream>
#include <chrono>
#include "FvmMesh2D.h"

using namespace std;
using namespace std::chrono;

int main()
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	FvmMesh2D finiteVolumeMesh;

	finiteVolumeMesh.msh_reader.readMesh();
	finiteVolumeMesh.msh_reader.constructIdNodes();

	finiteVolumeMesh.assign_vextex();
	finiteVolumeMesh.assign_faces();
	finiteVolumeMesh.assign_boundary_condition();
	finiteVolumeMesh.detect_nearest_neighbor();
	finiteVolumeMesh.write_vtk();

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(t2 - t1).count();

	cout << duration << " seconds." << endl;

    return 0;
}
