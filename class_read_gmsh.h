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
    vector<unsigned> id_node;
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
		stringstream ss = stringstream(line);
		vector <unsigned> line_number;
		while (!ss.eof()) {
			unsigned number;
			ss >> number;
			line_number.push_back(number);
			//cout << number << " ";
		}
		//cout << endl;
		node_msh.id_node  = line_number;
		node_msh.ident = line_number[0];
		node_msh.elem_typ = line_number[1];
		node_msh.nb_tags = line_number[2];
		node_msh.tag1 = line_number[3];
		node_msh.tag2 = line_number[4];
		id_nodes_msh.push_back(node_msh);
		unsigned elem_typ = id_nodes_msh[i].elem_typ;
		switch (elem_typ)
		{
		case 1:  // 2 - node line.
			break;
		case 3:  // 4-node quadrangle.
			nbelm = nbelm + 1;
			break;
		case 15: // 1-node point.
			break;
		case 37: // 5-node edge quadrangle.	
			nbelm = nbelm + 1;
			break;
		case 27: // boundary 5-node edge.
			break;
		default:
			throw runtime_error("Element type is not suppoted. Comming soon !");
			break;
		}
	}

}

#endif // CLASS_READ_GMSH_H_INCLUDED
