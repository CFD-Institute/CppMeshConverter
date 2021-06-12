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
    GmshReader msh_reader;
    vector<Cell2D> cells;
    void assign_vextex();
    void assign_faces();
    void assign_boundary_condition();
    void detect_nearest_neighbor();
    void calcul_vol_cells();
    void write_vtk();
};

#endif /* FVMMESH2D_H */

