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
    vector<node_ident> id_nodes;
    vector<node_ident_msh> id_nodes_msh;

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

	for (unsigned i = 0; i < nbnode; i++)
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

	for (unsigned i = 0; i < nbel_msh; i++)
	{
		line = ReadLine(stream_msh);
		node_ident_msh node_msh;
		stringstream(line) >> node_msh.ident >> node_msh.elem_typ >> node_msh.nb_tags >> node_msh.tag1 >> node_msh.tag2;
		id_nodes_msh.push_back(node_msh);
		unsigned elem_typ = id_nodes_msh[i].elem_typ;
		switch (elem_typ)
		{
		case 1:  // 2 - node line.
			id_nodes_msh[i].id_node = new unsigned[7];
			break;
		case 3:  // 4-node quadrangle.
			id_nodes_msh[i].id_node = new unsigned[9];
			nbelm = nbelm + 1;
			break;
		case 15: // 1-node point.
			id_nodes_msh[i].id_node = new unsigned[6];
			break;
		case 37: // 5-node edge quadrangle.
			id_nodes_msh[i].id_node = new unsigned[30];
			nbelm = nbelm + 1;
			break;
		case 27: // boundary 5-node edge.
			id_nodes_msh[i].id_node = new unsigned[10];
			break;
		default:
			throw runtime_error("Element type is not suppoted. Comming soon !");
			break;
		}
	}

}

#endif // CLASS_READ_GMSH_H_INCLUDED
