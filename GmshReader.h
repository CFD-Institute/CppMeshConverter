#pragma once

#include <vector>
#include "Point.h"
#include "NodeIdent.h"
#include "NodeIdentMsh.h"

using namespace std;

class GmshReader {

public:

    GmshReader();
    void readMesh();
    void constructIdNodes();
    unsigned getNbNode();
    unsigned getNbElMsh();
    unsigned getNbElm();
    string getFname();
    vector<Point> getCoordNodes();
    vector<NodeIdent> getIdNodes();
    vector<NodeIdentMsh> getIdNodesMsh();
    GmshReader* setNbNode(unsigned);
    GmshReader* setNbElMsh(unsigned);
    GmshReader* setNbElm(unsigned);
    GmshReader* setFname(string);

private:
    GmshReader(const GmshReader &gmshReader);             // override default copy constructor
    GmshReader & operator = (const GmshReader &gmshReader); // and assignment operator
    unsigned nbNode;
    unsigned nbElMsh;
    unsigned nbElm;
    string fName;
    vector<Point> coordNodes;
    vector<NodeIdent> idNodes;
    vector<NodeIdentMsh> idNodesMsh;

};