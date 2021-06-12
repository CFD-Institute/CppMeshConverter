#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "FvmMesh2D.h"
#include "GmshReader.h"

void FvmMesh2D::assign_vextex() {
    for (unsigned i = 0; i < msh_reader.getNbElm(); i++) {

    Cell2D a_cell;

    a_cell.setIdent(i);
                
    NodeIdent nodeIdent = msh_reader.getIdNodes()[i];

    unsigned idnode = nodeIdent.getIdNode()[5];

    for (unsigned j = 0; j < msh_reader.getNbNode(); j++) {
	if (idnode == msh_reader.getCoordNodes()[j].getId()) {
            double x = msh_reader.getCoordNodes()[j].getX();
            double y = msh_reader.getCoordNodes()[j].getY();
            double z = msh_reader.getCoordNodes()[j].getZ();
            a_cell.setVertex1(Point(x, y, z, idnode));
	}
    }

    idnode = nodeIdent.getIdNode()[6];

    for (unsigned j = 0; j < msh_reader.getNbNode(); j++) {
	if (idnode == msh_reader.getCoordNodes()[j].getId()) {
            double x = msh_reader.getCoordNodes()[j].getX();
            double y = msh_reader.getCoordNodes()[j].getY();
            double z = msh_reader.getCoordNodes()[j].getZ();
            a_cell.setVertex2(Point(x, y, z, idnode));
	}
    }

    idnode = nodeIdent.getIdNode()[7];

    for (unsigned j = 0; j < msh_reader.getNbNode(); j++) {
	if (idnode == msh_reader.getCoordNodes()[j].getId()) {
            double x = msh_reader.getCoordNodes()[j].getX();
            double y = msh_reader.getCoordNodes()[j].getY();
            double z = msh_reader.getCoordNodes()[j].getZ();
            a_cell.setVertex3(Point(x, y, z, idnode));
        }
    }

    idnode = nodeIdent.getIdNode()[8];

    for (unsigned j = 0; j < msh_reader.getNbNode(); j++) {
        if (idnode == msh_reader.getCoordNodes()[j].getId()) {
            double x = msh_reader.getCoordNodes()[j].getX();
            double y = msh_reader.getCoordNodes()[j].getY();
            double z = msh_reader.getCoordNodes()[j].getZ();
            a_cell.setVertex4(Point(x, y, z, idnode));
	}
    }

    this->cells.push_back(a_cell);
    }
}

void FvmMesh2D::assign_faces() {
    for (unsigned i = 0; i < msh_reader.getNbElm(); i++) {
	this->cells[i].getFace()[0].setP1(this->cells[i].getVertex()[0]);
	this->cells[i].getFace()[0].setP2(this->cells[i].getVertex()[1]);

	this->cells[i].getFace()[1].setP1(this->cells[i].getVertex()[1]);
	this->cells[i].getFace()[1].setP2(this->cells[i].getVertex()[2]);

	this->cells[i].getFace()[2].setP1(this->cells[i].getVertex()[2]);
	this->cells[i].getFace()[2].setP2(this->cells[i].getVertex()[3]);

	this->cells[i].getFace()[3].setP1(this->cells[i].getVertex()[3]);
	this->cells[i].getFace()[3].setP2(this->cells[i].getVertex()[0]);
    }
}

void FvmMesh2D::assign_boundary_condition() {
    for (unsigned i = 0; i < msh_reader.getNbElm(); i++) {
	unsigned idnode1 = this->cells[i].getVertex()[0].getId();
	unsigned idnode2 = this->cells[i].getVertex()[1].getId();

	for (auto it = msh_reader.getIdNodesMsh().begin(); it != msh_reader.getIdNodesMsh().end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    this->cells[i].getFace()[0].setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    this->cells[i].getFace()[0].setBcTyp(it->getTag1()) ;
		}
            }
	}

	idnode1 = this->cells[i].getVertex()[1].getId();
	idnode2 = this->cells[i].getVertex()[2].getId();

	for (auto it = msh_reader.getIdNodesMsh().begin(); it != msh_reader.getIdNodesMsh().end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    this->cells[i].getFace()[1].setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    this->cells[i].getFace()[1].setBcTyp(it->getTag1()) ;
		}
            }
	}

	idnode1 = this->cells[i].getVertex()[2].getId();
	idnode2 = this->cells[i].getVertex()[3].getId();

	for (auto it = msh_reader.getIdNodesMsh().begin(); it != msh_reader.getIdNodesMsh().end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    this->cells[i].getFace()[2].setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    this->cells[i].getFace()[2].setBcTyp(it->getTag1()) ;
		}
            }
	}

	idnode1 = this->cells[i].getVertex()[3].getId();
	idnode2 = this->cells[i].getVertex()[0].getId();

	for (auto it = msh_reader.getIdNodesMsh().begin(); it != msh_reader.getIdNodesMsh().end(); ++it) {
            if (it->getElemTyp() == 27) {
		if (it->getIdNode()[5] == idnode1 && it->getIdNode()[6] == idnode2) {
                    this->cells[i].getFace()[3].setBcTyp(it->getTag1()) ;
		} else if (it->getIdNode()[5] == idnode2 && it->getIdNode()[6] == idnode1) {
                    this->cells[i].getFace()[3].setBcTyp(it->getTag1()) ;
		}
            }
	}

    }
}

void FvmMesh2D::calcul_vol_cells() {
    unsigned i = 0;

    for (auto it = this->cells.begin(); it != this->cells.end(); ++it) {
	this->cells[i].setVol(this->cells[i].getVol());
	i = i + 1;
    }
}

void FvmMesh2D::detect_nearest_neighbor() {
    unsigned nbelm = msh_reader.getNbElm();
    
    for (unsigned i = 0; i < nbelm; i++) {
	unsigned idnode1 = this->cells[i].getVertex()[0].getId();
	unsigned idnode2 = this->cells[i].getVertex()[1].getId();

	Cell2D *curr_cell = &this->cells[i];

	for (unsigned j = 0; j < nbelm; j++) {
            Cell2D *runn_cell = &this->cells[j];
            
            if (curr_cell != runn_cell) {
		unsigned cnt = 0;
		for (unsigned t = 0; t < 4; t++) {
                    if (idnode1 == runn_cell->getVertex()[t].getId()) cnt = cnt + 1;
                    if (idnode2 == runn_cell->getVertex()[t].getId()) cnt = cnt + 1;
		}
		
                if (cnt == 2) {
                    this->cells[i].setNeighbor1(runn_cell);
		}
            }
	}
    }

    for (unsigned i = 0; i < nbelm; i++) {
	unsigned idnode1 = this->cells[i].getVertex()[1].getId();
	unsigned idnode2 = this->cells[i].getVertex()[2].getId();

	Cell2D *curr_cell = &this->cells[i];

	for (unsigned j = 0; j < nbelm; j++) {
            Cell2D *runn_cell = &this->cells[j];
            
            if (curr_cell != runn_cell) {
		unsigned cnt = 0;
		
                for (unsigned t = 0; t < 4; t++) {
                    if (idnode1 == runn_cell->getVertex()[t].getId()) cnt = cnt + 1;
                    if (idnode2 == runn_cell->getVertex()[t].getId()) cnt = cnt + 1;
		}
		
                if (cnt == 2) {
                    this->cells[i].setNeighbor2(runn_cell);
                }
            }
	}
    }

    for (unsigned i = 0; i < nbelm; i++) {
	unsigned idnode1 = this->cells[i].getVertex()[2].getId();
	unsigned idnode2 = this->cells[i].getVertex()[3].getId();

	Cell2D *curr_cell = &this->cells[i];

	for (unsigned j = 0; j < nbelm; j++) {
            Cell2D *runn_cell = &this->cells[j];
            
            if (curr_cell != runn_cell) {
		unsigned cnt = 0;
		
                for (unsigned t = 0; t < 4; t++) {
                    if (idnode1 == runn_cell->getVertex()[t].getId()) cnt = cnt + 1;
                    if (idnode2 == runn_cell->getVertex()[t].getId()) cnt = cnt + 1;
		}
		
                if (cnt == 2) {
                    this->cells[i].setNeighbor3(runn_cell);
		}
            }
	}

    }

    for (unsigned i = 0; i < nbelm; i++) {
	unsigned idnode1 = this->cells[i].getVertex()[3].getId();
	unsigned idnode2 = this->cells[i].getVertex()[0].getId();

	Cell2D *curr_cell = &this->cells[i];

	for (unsigned j = 0; j < nbelm; j++) {
            Cell2D *runn_cell = &this->cells[j];
            
            if (curr_cell != runn_cell) {
		unsigned cnt = 0;
		
                for (unsigned t = 0; t < 4; t++) {
                    if (idnode1 == runn_cell->getVertex()[t].getId()) cnt = cnt + 1;
                    if (idnode2 == runn_cell->getVertex()[t].getId()) cnt = cnt + 1;
		}
		
                if (cnt == 2) {
                    this->cells[i].setNeighbor4(runn_cell);
		}
            }
	}

    }
}

void FvmMesh2D::write_vtk() {
    string str = msh_reader.getFname() + ".vtk";
    ofstream outfile(str);
    outfile.setf(ios::fixed, ios::floatfield);
    outfile.precision(10);
    outfile << "# vtk DataFile Version 2.0" << endl;
    outfile << "VTK Format for unstructured grid" << endl;
    outfile << "ASCII" << endl;
    outfile << "DATASET POLYDATA" << endl;
    outfile << "POINTS " << msh_reader.getNbNode() << " float" << endl;

    for (unsigned i = 0; i < msh_reader.getNbNode(); i++) {
	outfile << setw(15) << msh_reader.getCoordNodes()[i].getX() << " " << setw(15) << msh_reader.getCoordNodes()[i].getY() << " " << setw(15) << 0.0f << " " << endl;
    }

    outfile << "POLYGONS " << msh_reader.getNbElm() << " " << 5 * msh_reader.getNbElm() << endl;

    for (unsigned i = 0; i < msh_reader.getNbElm(); i++) {
        outfile << 4 << " " << msh_reader.getIdNodes()[i].getIdNode()[5] - 1 << " " << msh_reader.getIdNodes()[i].getIdNode()[6] - 1 << " " << msh_reader.getIdNodes()[i].getIdNode()[7] - 1 << " " << msh_reader.getIdNodes()[i].getIdNode()[8] - 1 << endl;
    }

    outfile << "CELL_DATA " << msh_reader.getNbElm() << endl;
    outfile << "SCALARS CELL_IDENT integer 1" << endl;
    outfile << "LOOKUP_TABLE default " << endl;

    for (unsigned i = 0; i < msh_reader.getNbElm(); i++) {
        outfile << this->cells[i].getIdent() << endl;
    }

    outfile << "SCALARS NEIGHBOR1 integer 1" << endl;
    outfile << "LOOKUP_TABLE default " << endl;
	
    for (unsigned i = 0; i < msh_reader.getNbElm(); i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor1();
	
        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << endl;
	} else {
            outfile << -1 << endl;
	}
    }

    outfile << "SCALARS NEIGHBOR2 integer 1" << endl;
    outfile << "LOOKUP_TABLE default " << endl;
	
    for (unsigned i = 0; i < msh_reader.getNbElm(); i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor2();
	
        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << endl;
	} else {
            outfile << -1 << endl;
	}
    }

    outfile << "SCALARS NEIGHBOR3 integer 1" << endl;
    outfile << "LOOKUP_TABLE default " << endl;
	
    for (unsigned i = 0; i < msh_reader.getNbElm(); i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor3();
	
        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << endl;
	} else {
            outfile << -1 << endl;
	}
    }

    outfile << "SCALARS NEIGHBOR4 integer 1" << endl;
    outfile << "LOOKUP_TABLE default " << endl;
	
    for (unsigned i = 0; i < msh_reader.getNbElm(); i++) {
	Cell2D *curr_cell = this->cells[i].getNeighbor4();
	
        if (curr_cell != nullptr) {
            outfile << curr_cell->getIdent() << endl;
	} else {
            outfile << -1 << endl;
	}
    }

    outfile.close();
}

