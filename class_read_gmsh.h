#ifndef CLASS_READ_GMSH_H_INCLUDED
#define CLASS_READ_GMSH_H_INCLUDED

#include <vector>
#include <iostream>
#include <sstream>
#include "class_point.h"
#include "streamIO.h"

using namespace std;

struct node_ident
{
    unsigned *id_node;
};

struct node_ident_msh: public node_ident
{
    unsigned ident;
    unsigned elem_typ;
    unsigned nb_tags;
    unsigned tag1;
    unsigned tag2;
};

class GmshReader : public point{

public:
    unsigned nbnode;
    unsigned nbel_msh;
    unsigned nbelm;
    string fname;

    GmshReader();
    void read_mesh();

protected:
    vector<point> coord_nodes;
    node_ident id_nodes;
    node_ident_msh id_nodes_msh;

};

GmshReader::GmshReader()
{
    this -> nbnode   = 0;
    this -> nbelm    = 0;
    this -> nbel_msh = 0;
    this -> fname    = "";
}

void GmshReader::read_mesh()
{
    // open input file
    fname = "input.dat";
    ifstream stream( fname );
    if (stream.fail()) throw runtime_error( "could not open input file." );

    string str;
    str = ReadLine( stream );

	// open mesh file .msh of GMSH
	string str_msh = str + ".msh";
	ifstream stream_msh(str_msh);
	if (stream_msh.fail()) throw runtime_error("could not open mesh file");

	string line;
	line = ReadLine(stream_msh);
	line = ReadLine(stream_msh);
	line = ReadLine(stream_msh);
	line = ReadLine(stream_msh);

	line = ReadLine(stream_msh);
	stringstream(line) >> nbnode;

	for (int i = 0; i < nbnode; i++)
	{
		line = ReadLine(stream_msh);
		unsigned ident;
		double x, y, z;
		stringstream(line) >> ident >> x >> y >> z;
		point p(x, y, z, ident);
		coord_nodes.push_back(p);
	}

	line = ReadLine(stream_msh);
	line = ReadLine(stream_msh);

	line = ReadLine(stream_msh);
	stringstream(line) >> nbel_msh;

}

#endif // CLASS_READ_GMSH_H_INCLUDED
