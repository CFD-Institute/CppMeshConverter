#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include "Point.h"
#include "NodeIdent.h"
#include "NodeIdentMsh.h"
#include "streamIO.h"

using namespace std;

class GmshReader {

public:
    unsigned nbnode;
    unsigned nbel_msh;
    unsigned nbelm;
    string fname;

    GmshReader();
    void read_mesh();
    void construct_id_nodes();

    vector<Point> coord_nodes;
    vector<NodeIdent> id_nodes;
    vector<NodeIdentMsh> id_nodes_msh;

private:
	GmshReader(const GmshReader &gmshReader);             // override default copy constructor
	GmshReader & operator = (const GmshReader &gmshReader); // and assignment operator

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
	fname = str;

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
		Point p(x, y, z, ident);
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
		stringstream ss = stringstream(line);  // no error with Visual C++ 2015, error with g++
		vector <unsigned> line_number;
		while (!ss.eof()) {
			unsigned number;
			ss >> number;
			line_number.push_back(number);
			//cout << number << " ";
		}
		//cout << endl;
		node_msh.idNode  = line_number;
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

void GmshReader::construct_id_nodes()
{
	for (unsigned i = 0; i < nbel_msh; i++)
	{
		if (id_nodes_msh[i].elem_typ == 3)
		{
			node_ident node;
			node.id_node = id_nodes_msh[i].id_node;
			id_nodes.push_back(node);
		}

		if (id_nodes_msh[i].elem_typ == 37)
		{
			node_ident node;
			node.id_node = id_nodes_msh[i].id_node;
			id_nodes.push_back(node);
		}
	}
}

