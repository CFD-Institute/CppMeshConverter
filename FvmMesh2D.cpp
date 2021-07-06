#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <vector>
#include "FvmMesh2D.h"
#include "GmshReader.h"

#include <algorithm>

using namespace std;

FvmMesh2D::FvmMesh2D() {
    mshReader.readMesh();
    mshReader.constructIdNodes();
}

vector<Cell2D> & FvmMesh2D::getCells() {
    return this->cells;
}

void FvmMesh2D::assignVertex() {
    vector<Point> coordNodes = mshReader.getCoordNodes();

    auto nodeIdents = mshReader.getIdNodes();
    for (unsigned i = 0; i < mshReader.getNbElm(); i++) {

    Cell2D aCell;

    aCell.setIdent(i);

    NodeIdent nodeIdent = nodeIdents[i];
    unsigned idnode     = nodeIdent.getIdNode()[5];

    auto begin = coordNodes.begin();
    auto end   = coordNodes.end();

    auto target_node = std::find_if(
        begin, end, [&](const Point& node) {
          return idnode == node.getId();
        });
    if (target_node    != end) {
      aCell.setVertex1(*target_node);
    }

    idnode = nodeIdent.getIdNode()[6];

    target_node = std::find_if(
        begin, end, [&](const Point& node) {
          return idnode == node.getId();
        });
    if (target_node    != end) {
      aCell.setVertex2(*target_node);
    }

    idnode = nodeIdent.getIdNode()[7];

    target_node = std::find_if(
        begin, end, [&](const Point& node) {
          return idnode == node.getId();
        });
    if (target_node    != end) {
      aCell.setVertex3(*target_node);
    }

    idnode = nodeIdent.getIdNode()[8];

    target_node = std::find_if(
        begin, end, [&](const Point& node) {
          return idnode == node.getId();
        });
    if (target_node    != end) {
      aCell.setVertex4(*target_node);
    }

    this->cells.push_back(aCell);
    }
}

void FvmMesh2D::assignFaces() {

  std::for_each(cells.begin(), cells.end(), [](Cell2D& cell) {


    cell.getFace1().setP1(cell.getVertex1());
    cell.getFace1().setP2(cell.getVertex2());

    cell.getFace2().setP1(cell.getVertex2());
    cell.getFace2().setP2(cell.getVertex3());

    cell.getFace3().setP1(cell.getVertex3());
    cell.getFace3().setP2(cell.getVertex4());

    cell.getFace4().setP1(cell.getVertex4());
    cell.getFace4().setP2(cell.getVertex1());});
}

void FvmMesh2D::assignBoundaryCondition() {
    vector<NodeIdentMsh> idNodeMsh = mshReader.getIdNodesMsh();

    for (Cell2D & cell : cells) {
	unsigned idnode1 = cell.getVertex1().getId();
	unsigned idnode2 = cell.getVertex2().getId();

	for (auto it = idNodeMsh.begin(); it != idNodeMsh.end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    cell.getFace1().setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    cell.getFace1().setBcTyp(it->getTag1()) ;
		}
            }
	}

	idnode1 = cell.getVertex2().getId();
	idnode2 = cell.getVertex3().getId();

	for (auto it = idNodeMsh.begin(); it != idNodeMsh.end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    cell.getFace2().setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    cell.getFace2().setBcTyp(it->getTag1()) ;
		}
            }
	}

	idnode1 = cell.getVertex3().getId();
	idnode2 = cell.getVertex4().getId();

	for (auto it = idNodeMsh.begin(); it != idNodeMsh.end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    cell.getFace3().setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    cell.getFace3().setBcTyp(it->getTag1()) ;
		}
            }
	}

	idnode1 = cell.getVertex4().getId();
	idnode2 = cell.getVertex1().getId();

	for (auto it = idNodeMsh.begin(); it != idNodeMsh.end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    cell.getFace4().setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    cell.getFace4().setBcTyp(it->getTag1()) ;
		}
            }
	}

    }
}

void FvmMesh2D::calculVol() {
//  unsigned i = 0;

  std::for_each(cells.begin(), cells.end(), [](Cell2D cell) {
    cell.setVol(cell.getVol());
    });
//    for (auto it = this->cells.begin(); it != this->cells.end(); ++it) {
//	this->cells[i].setVol(this->cells[i].getVol());
//	i = i + 1;
//    }
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
    outfile << "# vtk DataFile Version 2.0\n";
    outfile << "VTK Format for unstructured grid\n";
    outfile << "ASCII\n";
    outfile << "DATASET POLYDATA\n";
    outfile << "POINTS " << nbNodes << " float\n";

    for (unsigned i = 0; i < nbNodes; i++) {
	outfile << setw(15) << coordNodes[i].getX() << " " << setw(15) << coordNodes[i].getY() << " " << setw(15) << 0.0f << " \n";
    }

    outfile << "POLYGONS " << nbElm << " " << 5 * nbElm << '\n';
    outfile << flush;

    for (unsigned i = 0; i < nbElm; i++) {
        outfile << 4 << " " << idNodes[i].getIdNode()[5] - 1 << " " << idNodes[i].getIdNode()[6] - 1 << " " << idNodes[i].getIdNode()[7] - 1 << " " << idNodes[i].getIdNode()[8] - 1 << "\n";
    }

    outfile << "CELL_DATA " << nbElm << '\n';
    outfile << "SCALARS CELL_IDENT integer 1" << '\n';
    outfile << "LOOKUP_TABLE default " << endl;

    for (unsigned i = 0; i < nbElm; i++) {
        outfile << this->cells[i].getIdent() << '\n';
    }

    outfile << "SCALARS NEIGHBOR1 integer 1" << '\n';
    outfile << "LOOKUP_TABLE default " << '\n';

    for (unsigned i = 0; i < nbElm; i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor1();

        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << '\n';
	} else {
            outfile << -1 << '\n';
	}
    }

    outfile << "SCALARS NEIGHBOR2 integer 1" << '\n';
    outfile << "LOOKUP_TABLE default " << endl;

    for (unsigned i = 0; i < nbElm; i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor2();

        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << '\n';
	} else {
            outfile << -1 << '\n';
	}
    }

    outfile << "SCALARS NEIGHBOR3 integer 1" << '\n';
    outfile << "LOOKUP_TABLE default " << endl;

    for (unsigned i = 0; i < nbElm; i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor3();

        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << '\n';
	} else {
            outfile << -1 << '\n';
	}
    }

    outfile << "SCALARS NEIGHBOR4 integer 1" << '\n';
    outfile << "LOOKUP_TABLE default " << endl;

    for (unsigned i = 0; i < nbElm; i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor4();

        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << '\n';
	} else {
            outfile << -1 << '\n';
	}
    }

    outfile << flush;

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
    outfile << "VARIABLES=X,Y,CELL_IDENT,NEIGHBOR1,NEIGHBOR2,NEIGHBOR3,NEIGHBOR4" << '\n';
    outfile << "VARIABLES=X,Y" << '\n';
    outfile << "ZONE T=\"UNSTRUCTURED-COUNTOUR\"" << '\n';
    outfile << "ZONETYPE=FEPOLYGON" << '\n';
    outfile << "NODES=" << nbNodes << '\n';
    outfile << "ELEMENTS=" << nbElm << '\n';
    outfile << "FACES=" << nbElm * 4 << '\n';
    outfile << "NumConnectedBoundaryFaces=0" << '\n';
    outfile << "TotalNumBoundaryConnections=0" << '\n';

    for (unsigned i = 0; i < nbNodes; i++) {
      outfile << setw(15) << coordNodes[i].getX() << '\n';
    }
    outfile << flush;
    
    for (unsigned i = 0; i < nbNodes; i++) {
        outfile << setw(15) << coordNodes[i].getY() << '\n';
    }
    outfile << flush;

    /*
     * Node indexes
     */
    for (unsigned i = 0; i < nbElm; i++) {
        outfile << idNodes[i].getIdNode()[5] << " " << idNodes[i].getIdNode()[6] << '\n';
        outfile << idNodes[i].getIdNode()[6] << " " << idNodes[i].getIdNode()[7] << '\n';
        outfile << idNodes[i].getIdNode()[7] << " " << idNodes[i].getIdNode()[8] << '\n';
        outfile << idNodes[i].getIdNode()[8] << " " << idNodes[i].getIdNode()[5] << '\n';
    }
    outfile << flush;

    for (unsigned i = 0; i < nbElm; i++) {
        outfile << i + 1 << " " << i + 1 << " " << i + 1 << " " << i + 1 << " " << '\n';
    }
    outfile << flush;

    for (unsigned i = 0; i < nbElm; i++) {
        outfile << 0 << " " << 0 << " " << 0 << " " << 0 << " " << '\n';
    }
    outfile << flush;

    outfile.close();
}

