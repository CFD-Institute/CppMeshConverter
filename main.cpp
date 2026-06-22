#include <iostream>
#include "ExecutionTimer.h"
#include "FvmMesh2D.h"

int main()
{
    ExecutionTimer<std::chrono::milliseconds> timer;
    FvmMesh2D finiteVolumeMesh;

    finiteVolumeMesh.assignVertex();
    finiteVolumeMesh.assignFaces();
//	finiteVolumeMesh.assignBoundaryCondition();
    finiteVolumeMesh.detectNearestNeighbor();
    finiteVolumeMesh.writeTecplot();
    finiteVolumeMesh.writeVtk();   
    timer.stop(); 
    return 0;
}
