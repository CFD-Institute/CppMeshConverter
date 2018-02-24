#include <iostream>
#include "class_read_gmsh.h"

using namespace std;

int main()
{
    GmshReader gmsh_reader;
    gmsh_reader.read_mesh();

    return 0;
}
