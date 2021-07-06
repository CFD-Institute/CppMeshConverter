#include <iostream>
#include <chrono>
#include "FvmMesh2D.h"

using namespace std;
using namespace std::chrono;

int main()
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	FvmMesh2D finiteVolumeMesh;

	finiteVolumeMesh.assignVertex();
	finiteVolumeMesh.assignFaces();
//	finiteVolumeMesh.assignBoundaryCondition();
	finiteVolumeMesh.detectNearestNeighbor();
	finiteVolumeMesh.writeTecplot();
        finiteVolumeMesh.writeVtk();

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(t2 - t1).count();

	cout << duration << " milliseconds." << endl;

    return 0;
}
