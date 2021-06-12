/* 
 * File:   FvmMesh2D.h
 * Author: HP
 *
 * Created on June 12, 2021, 4:31 PM
 */

#ifndef FVMMESH2D_H
#define FVMMESH2D_H

#include <vector>
#include "Cell2D.h"
#include "GmshReader.h"

using namespace std;

class FvmMesh2D {

public:
    FvmMesh2D();
    vector<Cell2D> getCells();
    void assignVertex();
    void assignFaces();
    void assignBoundaryCondition();
    void detectNearestNeighbor();
    void calculVol();
    void writeVtk();
    
private:
    GmshReader mshReader;
    vector<Cell2D> cells;
};

#endif /* FVMMESH2D_H */

