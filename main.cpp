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
	finiteVolumeMesh.assignBoundaryCondition();
	finiteVolumeMesh.detectNearestNeighbor();
	finiteVolumeMesh.writeTecplot();

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(t2 - t1).count();

	cout << duration << " seconds." << endl;

    return 0;
}
