#include <iostream>
#include <sstream>
#include "streamIO.h"
#include "GmshReader.h"

using namespace std;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

GmshReader::GmshReader() {
    this -> setNbNode(0);
    this -> setNbElm(0);
    this -> setNbElMsh(0);
    this -> setFname("");
}

GmshReader* GmshReader::setNbNode(unsigned nbNode) {
    this->nbNode = nbNode;
    return this;
}

unsigned GmshReader::getNbNode() {
    return this->nbNode;
}

GmshReader* GmshReader::setNbElm(unsigned nbElm) {
    this->nbElm = nbElm;
    return this;
}

unsigned GmshReader::getNbElm() {
    return this->nbElm;
}

GmshReader* GmshReader::setNbElMsh(unsigned nbElMsh) {
    this->nbElMsh = nbElMsh;
    return this;
}

unsigned GmshReader::getNbElMsh() {
    return this->nbElMsh;
}

GmshReader* GmshReader::setFname(string fName) {
    this->fName = fName;
    return this;
}

string GmshReader::getFname() {
    return this->fName;
}

vector<NodeIdent> & GmshReader::getIdNodes() {
    return this->idNodes;
}

vector<NodeIdentMsh> & GmshReader::getIdNodesMsh() {
    return this->idNodesMsh;
}

vector<Point> & GmshReader::getCoordNodes() {
    return this->coordNodes;
}

void GmshReader::readMesh() {
    // open input file
    setFname("input.dat");
    ifstream stream( getFname() );
    if (stream.fail()) throw runtime_error( "could not open input file." );

    string str;
    str = ReadLine( stream );
    setFname(str);

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
    stringstream(line) >> nbNode;


    coordNodes.reserve(nbNode);
    for (unsigned i = 0; i < nbNode; i++) {
        line = ReadLine(stream_msh);
        unsigned ident;
	double x, y, z;
	stringstream(line) >> ident >> x >> y >> z;
	Point p(x, y, z, ident);
	coordNodes.push_back(p);
    }

    line = ReadLine(stream_msh);
    line = ReadLine(stream_msh);

    line = ReadLine(stream_msh);
    stringstream(line) >> nbElMsh;

    idNodesMsh.reserve(nbElMsh);
    for (unsigned i = 0; i < nbElMsh; i++) {
	line = ReadLine(stream_msh);
	NodeIdentMsh node_msh;
	stringstream ss = stringstream(line);  // no error with Visual C++ 2015, error with g++
	vector <unsigned> line_number;
	while (!ss.eof()) {
            unsigned number;
            ss >> number;
            line_number.push_back(number);
            //cout << number << " ";
        }
	//cout << endl;
	node_msh.setIdNode(line_number);
	node_msh.setIdent(line_number[0]);
	node_msh.setElemTyp(line_number[1]);
	node_msh.setNbTags(line_number[2]);
	node_msh.setTag1(line_number[3]);
	node_msh.setTag2(line_number[4]);

	idNodesMsh.push_back(node_msh);

	unsigned elem_typ = idNodesMsh[i].getElemTyp();

	switch (elem_typ) {
            case 1:  // 2 - node line.
		break;
            case 3:  // 4-node quadrangle.
                nbElm = nbElm + 1;
		break;
            case 15: // 1-node point.
		break;
            case 37: // 5-node edge quadrangle.
		nbElm = nbElm + 1;
		break;
            case 27: // boundary 5-node edge.
		break;
            default:
		throw runtime_error("Element type is not supported. Coming soon !");
		break;
	}
    }

}

void GmshReader::constructIdNodes() {
    idNodes.reserve(nbElMsh);
    for (unsigned i = 0; i < nbElMsh; i++) {
        unsigned elmTyp = idNodesMsh[i].getElemTyp();

        switch (elmTyp) {
            case 3:
            case 37:
                NodeIdent node;
                node.setIdNode(idNodesMsh[i].getIdNode());
                idNodes.push_back(node);
                break;
        }
    }
}

