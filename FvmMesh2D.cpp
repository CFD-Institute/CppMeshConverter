#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <vector>
#include "FvmMesh2D.h"
#include "GmshReader.h"

using namespace std;

FvmMesh2D::FvmMesh2D() {
    mshReader.readMesh();
    mshReader.constructIdNodes();
}

vector<Cell2D> & FvmMesh2D::getCells() {
    return this->cells;
}

void FvmMesh2D::assignVertex() {
    vector<Point> & coordNodes = mshReader.getCoordNodes();

    for (unsigned i = 0; i < mshReader.getNbElm(); i++) {

    Cell2D a_cell;

    a_cell.setIdent(i);

    NodeIdent nodeIdent = mshReader.getIdNodes()[i];
    unsigned idnode = nodeIdent.getIdNode()[5];

    for (unsigned j = 0; j < mshReader.getNbNode(); j++) {
	if (idnode == coordNodes[j].getId()) {
            double x = coordNodes[j].getX();
            double y = coordNodes[j].getY();
            double z = coordNodes[j].getZ();
            a_cell.setVertex1(Point(x, y, z, idnode));
            break;
	}
    }

    idnode = nodeIdent.getIdNode()[6];

    for (unsigned j = 0; j < mshReader.getNbNode(); j++) {
	if (idnode == coordNodes[j].getId()) {
            double x = coordNodes[j].getX();
            double y = coordNodes[j].getY();
            double z = coordNodes[j].getZ();
            a_cell.setVertex2(Point(x, y, z, idnode));
            break;
	}
    }

    idnode = nodeIdent.getIdNode()[7];

    for (unsigned j = 0; j < mshReader.getNbNode(); j++) {
	if (idnode == coordNodes[j].getId()) {
            double x = coordNodes[j].getX();
            double y = coordNodes[j].getY();
            double z = coordNodes[j].getZ();
            a_cell.setVertex3(Point(x, y, z, idnode));
            break;
        }
    }

    idnode = nodeIdent.getIdNode()[8];

    for (unsigned j = 0; j < mshReader.getNbNode(); j++) {
        if (idnode == coordNodes[j].getId()) {
            double x = coordNodes[j].getX();
            double y = coordNodes[j].getY();
            double z = coordNodes[j].getZ();
            a_cell.setVertex4(Point(x, y, z, idnode));
            break;
	}
    }

    this->cells.push_back(a_cell);
    }
}

void FvmMesh2D::assignFaces() {
    for (unsigned i = 0; i < mshReader.getNbElm(); i++) {
	this->cells[i].getFace1().setP1(this->cells[i].getVertex1());
	this->cells[i].getFace1().setP2(this->cells[i].getVertex2());

	this->cells[i].getFace2().setP1(this->cells[i].getVertex2());
	this->cells[i].getFace2().setP2(this->cells[i].getVertex3());

	this->cells[i].getFace3().setP1(this->cells[i].getVertex3());
	this->cells[i].getFace3().setP2(this->cells[i].getVertex4());

	this->cells[i].getFace4().setP1(this->cells[i].getVertex4());
	this->cells[i].getFace4().setP2(this->cells[i].getVertex1());
    }
}

void FvmMesh2D::assignBoundaryCondition() {
    vector<NodeIdentMsh> idNodeMsh = mshReader.getIdNodesMsh();

    for (unsigned i = 0; i < mshReader.getNbElm(); i++) {
	unsigned idnode1 = this->cells[i].getVertex1().getId();
	unsigned idnode2 = this->cells[i].getVertex2().getId();

	for (auto it = idNodeMsh.begin(); it != idNodeMsh.end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    this->cells[i].getFace1().setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    this->cells[i].getFace1().setBcTyp(it->getTag1()) ;
		}
            }
	}

	idnode1 = this->cells[i].getVertex2().getId();
	idnode2 = this->cells[i].getVertex3().getId();

	for (auto it = idNodeMsh.begin(); it != idNodeMsh.end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    this->cells[i].getFace2().setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    this->cells[i].getFace2().setBcTyp(it->getTag1()) ;
		}
            }
	}

	idnode1 = this->cells[i].getVertex3().getId();
	idnode2 = this->cells[i].getVertex4().getId();

	for (auto it = idNodeMsh.begin(); it != idNodeMsh.end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    this->cells[i].getFace3().setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    this->cells[i].getFace3().setBcTyp(it->getTag1()) ;
		}
            }
	}

	idnode1 = this->cells[i].getVertex4().getId();
	idnode2 = this->cells[i].getVertex1().getId();

	for (auto it = idNodeMsh.begin(); it != idNodeMsh.end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    this->cells[i].getFace4().setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    this->cells[i].getFace4().setBcTyp(it->getTag1()) ;
		}
            }
	}

    }
}

void FvmMesh2D::calculVol() {
    unsigned i = 0;

    for (auto it = this->cells.begin(); it != this->cells.end(); ++it) {
	this->cells[i].setVol(this->cells[i].getVol());
	i = i + 1;
    }
}

void FvmMesh2D::detectNearestNeighbor() {
    unsigned nbelm = mshReader.getNbElm();

    for (unsigned i = 0; i < nbelm; i++) {
	unsigned idnode1 = this->cells[i].getVertex1().getId();
	unsigned idnode2 = this->cells[i].getVertex2().getId();

	Cell2D *curr_cell = &this->cells[i];

	for (unsigned j = 0; j < nbelm; j++) {
            Cell2D *runn_cell = &this->cells[j];

            if (curr_cell != runn_cell) {
		unsigned cnt = 0;

                if (idnode1 == runn_cell->getVertex1().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex1().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex2().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex2().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex3().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex3().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex4().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex4().getId()) cnt = cnt + 1;

                if (cnt == 2) {
                    this->cells[i].setNeighbor1(runn_cell);
		}
            }
	}
    }

    for (unsigned i = 0; i < nbelm; i++) {
	unsigned idnode1 = this->cells[i].getVertex2().getId();
	unsigned idnode2 = this->cells[i].getVertex3().getId();

	Cell2D *curr_cell = &this->cells[i];

	for (unsigned j = 0; j < nbelm; j++) {
            Cell2D *runn_cell = &this->cells[j];

            if (curr_cell != runn_cell) {
		unsigned cnt = 0;

                if (idnode1 == runn_cell->getVertex1().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex1().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex2().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex2().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex3().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex3().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex4().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex4().getId()) cnt = cnt + 1;

                if (cnt == 2) {
                    this->cells[i].setNeighbor2(runn_cell);
                }
            }
	}
    }

    for (unsigned i = 0; i < nbelm; i++) {
	unsigned idnode1 = this->cells[i].getVertex3().getId();
	unsigned idnode2 = this->cells[i].getVertex4().getId();

	Cell2D *curr_cell = &this->cells[i];

	for (unsigned j = 0; j < nbelm; j++) {
            Cell2D *runn_cell = &this->cells[j];

            if (curr_cell != runn_cell) {
		unsigned cnt = 0;

                if (idnode1 == runn_cell->getVertex1().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex1().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex2().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex2().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex3().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex3().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex4().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex4().getId()) cnt = cnt + 1;

                if (cnt == 2) {
                    this->cells[i].setNeighbor3(runn_cell);
		}
            }
	}

    }

    for (unsigned i = 0; i < nbelm; i++) {
	unsigned idnode1 = this->cells[i].getVertex4().getId();
	unsigned idnode2 = this->cells[i].getVertex1().getId();

	Cell2D *curr_cell = &this->cells[i];

	for (unsigned j = 0; j < nbelm; j++) {
            Cell2D *runn_cell = &this->cells[j];

            if (curr_cell != runn_cell) {
		unsigned cnt = 0;

                if (idnode1 == runn_cell->getVertex1().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex1().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex2().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex2().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex3().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex3().getId()) cnt = cnt + 1;

                if (idnode1 == runn_cell->getVertex4().getId()) cnt = cnt + 1;
                if (idnode2 == runn_cell->getVertex4().getId()) cnt = cnt + 1;

                if (cnt == 2) {
                    this->cells[i].setNeighbor4(runn_cell);
		}
            }
	}

    }
}

void FvmMesh2D::writeVtk() {
    string str = mshReader.getFname() + ".vtk";
    vector<Point> coordNodes  = mshReader.getCoordNodes();
    vector<NodeIdent> idNodes = mshReader.getIdNodes();
    unsigned nbNodes = mshReader.getNbNode();
    unsigned nbElm = mshReader.getNbElm();
    ofstream outfile(str);

    outfile.setf(ios::fixed, ios::floatfield);
    outfile.precision(10);
    outfile << "# vtk DataFile Version 2.0" << endl;
    outfile << "VTK Format for unstructured grid" << endl;
    outfile << "ASCII" << endl;
    outfile << "DATASET POLYDATA" << endl;
    outfile << "POINTS " << nbNodes << " float" << endl;

    for (unsigned i = 0; i < nbNodes; i++) {
	outfile << setw(15) << coordNodes[i].getX() << " " << setw(15) << coordNodes[i].getY() << " " << setw(15) << 0.0f << " " << endl;
    }

    outfile << "POLYGONS " << nbElm << " " << 5 * nbElm << endl;

    for (unsigned i = 0; i < nbElm; i++) {
        outfile << 4 << " " << idNodes[i].getIdNode()[5] - 1 << " " << idNodes[i].getIdNode()[6] - 1 << " " << idNodes[i].getIdNode()[7] - 1 << " " << idNodes[i].getIdNode()[8] - 1 << endl;
    }

    outfile << "CELL_DATA " << nbElm << endl;
    outfile << "SCALARS CELL_IDENT integer 1" << endl;
    outfile << "LOOKUP_TABLE default " << endl;

    for (unsigned i = 0; i < nbElm; i++) {
        outfile << this->cells[i].getIdent() << endl;
    }

    outfile << "SCALARS NEIGHBOR1 integer 1" << endl;
    outfile << "LOOKUP_TABLE default " << endl;

    for (unsigned i = 0; i < nbElm; i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor1();

        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << endl;
	} else {
            outfile << -1 << endl;
	}
    }

    outfile << "SCALARS NEIGHBOR2 integer 1" << endl;
    outfile << "LOOKUP_TABLE default " << endl;

    for (unsigned i = 0; i < nbElm; i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor2();

        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << endl;
	} else {
            outfile << -1 << endl;
	}
    }

    outfile << "SCALARS NEIGHBOR3 integer 1" << endl;
    outfile << "LOOKUP_TABLE default " << endl;

    for (unsigned i = 0; i < nbElm; i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor3();

        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << endl;
	} else {
            outfile << -1 << endl;
	}
    }

    outfile << "SCALARS NEIGHBOR4 integer 1" << endl;
    outfile << "LOOKUP_TABLE default " << endl;

    for (unsigned i = 0; i < nbElm; i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor4();

        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << endl;
	} else {
            outfile << -1 << endl;
	}
    }

    outfile.close();
}

void FvmMesh2D::writeTecplot() {
    /* 
     * Write converted mesh file in Tecplot 2009 compatible format
     */
    string str = mshReader.getFname() + ".dat";
    vector<Point> coordNodes  = mshReader.getCoordNodes();
    vector<NodeIdent> idNodes = mshReader.getIdNodes();
    unsigned nbNodes = mshReader.getNbNode();
    unsigned nbElm = mshReader.getNbElm();
    ofstream outfile(str);

    outfile.setf(ios::fixed, ios::floatfield);
    outfile.precision(10);
    outfile << "VARIABLES=X,Y,CELL_IDENT,NEIGHBOR1,NEIGHBOR2,NEIGHBOR3,NEIGHBOR4" << endl;
    outfile << "VARIABLES=X,Y" << endl;
    outfile << "ZONE T=\"UNSTRUCTURED-COUNTOUR\"" << endl;
    outfile << "ZONETYPE=FEPOLYGON" << endl;
    outfile << "NODES=" << nbNodes << endl;
    outfile << "ELEMENTS=" << nbElm << endl;
    outfile << "FACES=" << nbElm * 4 << endl;
    outfile << "NumConnectedBoundaryFaces=0" << endl;
    outfile << "TotalNumBoundaryConnections=0" << endl;

    for (unsigned i = 0; i < nbNodes; i++) {
	outfile << setw(15) << coordNodes[i].getX() << endl;
    }
    
    for (unsigned i = 0; i < nbNodes; i++) {
	outfile << setw(15) << coordNodes[i].getY() << endl;
    }

    /*
     * Node indexes
     */
    for (unsigned i = 0; i < nbElm; i++) {
        outfile << idNodes[i].getIdNode()[5] << " " << idNodes[i].getIdNode()[6] << endl;
        outfile << idNodes[i].getIdNode()[6] << " " << idNodes[i].getIdNode()[7] << endl;
        outfile << idNodes[i].getIdNode()[7] << " " << idNodes[i].getIdNode()[8] << endl;
        outfile << idNodes[i].getIdNode()[8] << " " << idNodes[i].getIdNode()[5] << endl;
    }

    for (unsigned i = 0; i < nbElm; i++) {
        outfile << i + 1 << " " << i + 1 << " " << i + 1 << " " << i + 1 << " " << endl;
    }

    for (unsigned i = 0; i < nbElm; i++) {
        outfile << 0 << " " << 0 << " " << 0 << " " << 0 << " " << endl;
    }

    outfile.close();
}

