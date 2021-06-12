/* 
 * File:   FvmMesh2D.h
 * Author: HP
 *
 * Created on June 12, 2021, 4:31 PM
 */

#ifndef FVMMESH2D_H
#define FVMMESH2D_H

#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>

class list_cell_2D {

public:
	GmshReader msh_reader;
	vector<cell_2D> cells;
	void assign_vextex();
	void assign_faces();
	void assign_boundary_condition();
	void detect_nearest_neighbor();
	void calcul_vol_cells();
	void write_vtk();
};

void list_cell_2D::assign_vextex()
{
	for (unsigned i = 0; i < msh_reader.nbelm; i++) {

		cell_2D a_cell;

		a_cell.ident = i;

		int idnode = msh_reader.id_nodes[i].id_node[5];

		for (unsigned j = 0; j < msh_reader.nbnode; j++)
		{
			if (idnode == msh_reader.coord_nodes[j].get_ident())
			{
				double x = msh_reader.coord_nodes[j].get_x();
				double y = msh_reader.coord_nodes[j].get_y();
				double z = msh_reader.coord_nodes[j].get_z();
				a_cell.vertex[0] = point(x, y, z, idnode);
			}
		}

		idnode = msh_reader.id_nodes[i].id_node[6];

		for (unsigned j = 0; j < msh_reader.nbnode; j++)
		{
			if (idnode == msh_reader.coord_nodes[j].get_ident())
			{
				double x = msh_reader.coord_nodes[j].get_x();
				double y = msh_reader.coord_nodes[j].get_y();
				double z = msh_reader.coord_nodes[j].get_z();
				a_cell.vertex[1] = point(x, y, z, idnode);
			}
		}

		idnode = msh_reader.id_nodes[i].id_node[7];

		for (unsigned j = 0; j < msh_reader.nbnode; j++)
		{
			if (idnode == msh_reader.coord_nodes[j].get_ident())
			{
				double x = msh_reader.coord_nodes[j].get_x();
				double y = msh_reader.coord_nodes[j].get_y();
				double z = msh_reader.coord_nodes[j].get_z();
				a_cell.vertex[2] = point(x, y, z, idnode);
			}
		}

		idnode = msh_reader.id_nodes[i].id_node[8];

		for (unsigned j = 0; j < msh_reader.nbnode; j++)
		{
			if (idnode == msh_reader.coord_nodes[j].get_ident())
			{
				double x = msh_reader.coord_nodes[j].get_x();
				double y = msh_reader.coord_nodes[j].get_y();
				double z = msh_reader.coord_nodes[j].get_z();
				a_cell.vertex[3] = point(x, y, z, idnode);
			}
		}

		this->cells.push_back(a_cell);
	}
}

void list_cell_2D::assign_faces()
{
	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		this->cells[i].faces[0].p1 = this->cells[i].vertex[0];
		this->cells[i].faces[0].p2 = this->cells[i].vertex[1];

		this->cells[i].faces[1].p1 = this->cells[i].vertex[1];
		this->cells[i].faces[1].p2 = this->cells[i].vertex[2];

		this->cells[i].faces[2].p1 = this->cells[i].vertex[2];
		this->cells[i].faces[2].p2 = this->cells[i].vertex[3];

		this->cells[i].faces[3].p1 = this->cells[i].vertex[3];
		this->cells[i].faces[3].p2 = this->cells[i].vertex[0];
	}
}

void list_cell_2D::assign_boundary_condition()
{
	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		unsigned idnode1 = this->cells[i].vertex[0].get_ident();
		unsigned idnode2 = this->cells[i].vertex[1].get_ident();

		for (auto it = msh_reader.id_nodes_msh.begin(); it != msh_reader.id_nodes_msh.end(); ++it)
		{
			if (it->elem_typ == 27)
			{
				if (it->id_node[5] == idnode1 && it->id_node[6] == idnode2)
				{
					this->cells[i].faces[0].bc_typ = it->tag1;
				}
				else if (it->id_node[5] == idnode2 && it->id_node[6] == idnode1)
				{
					this->cells[i].faces[0].bc_typ = it->tag1;
				}
			}
		}

		idnode1 = this->cells[i].vertex[1].get_ident();
		idnode2 = this->cells[i].vertex[2].get_ident();

		for (auto it = msh_reader.id_nodes_msh.begin(); it != msh_reader.id_nodes_msh.end(); ++it)
		{
			if (it->elem_typ == 27)
			{
				if (it->id_node[5] == idnode1 && it->id_node[6] == idnode2)
				{
					this->cells[i].faces[1].bc_typ = it->tag1;
				}
				else if (it->id_node[5] == idnode2 && it->id_node[6] == idnode1)
				{
					this->cells[i].faces[1].bc_typ = it->tag1;
				}
			}
		}

		idnode1 = this->cells[i].vertex[2].get_ident();
		idnode2 = this->cells[i].vertex[3].get_ident();

		for (auto it = msh_reader.id_nodes_msh.begin(); it != msh_reader.id_nodes_msh.end(); ++it)
		{
			if (it->elem_typ == 27)
			{
				if (it->id_node[5] == idnode1 && it->id_node[6] == idnode2)
				{
					this->cells[i].faces[2].bc_typ = it->tag1;
				}
				else if (it->id_node[5] == idnode2 && it->id_node[6] == idnode1)
				{
					this->cells[i].faces[2].bc_typ = it->tag1;
				}
			}
		}

		idnode1 = this->cells[i].vertex[3].get_ident();
		idnode2 = this->cells[i].vertex[0].get_ident();

		for (auto it = msh_reader.id_nodes_msh.begin(); it != msh_reader.id_nodes_msh.end(); ++it)
		{
			if (it->elem_typ == 27)
			{
				if (it->id_node[5] == idnode1 && it->id_node[6] == idnode2)
				{
					this->cells[i].faces[3].bc_typ = it->tag1;
				}
				else if (it->id_node[5] == idnode2 && it->id_node[6] == idnode1)
				{
					this->cells[i].faces[3].bc_typ = it->tag1;
				}
			}
		}

	}
}

void list_cell_2D::calcul_vol_cells()
{
	unsigned i = 0;

	for (auto it = this->cells.begin(); it != this->cells.end(); ++it)
	{
		this->cells[i].calcul_vol();
		i = i + 1;
	}
}

void list_cell_2D::detect_nearest_neighbor()
{
	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		unsigned idnode1 = this->cells[i].vertex[0].get_ident();
		unsigned idnode2 = this->cells[i].vertex[1].get_ident();

		cell_2D *curr_cell = &this->cells[i];

		for (unsigned j = 0; j < msh_reader.nbelm; j++)
		{
			cell_2D *runn_cell = &this->cells[j];
			if (curr_cell != runn_cell) 
			{
				unsigned cnt = 0;
				for (unsigned t = 0; t < 4; t++)
				{
					if (idnode1 == runn_cell->vertex[t].get_ident()) cnt = cnt + 1;
					if (idnode2 == runn_cell->vertex[t].get_ident()) cnt = cnt + 1;
				}
				if (cnt == 2)
				{
					this->cells[i].neighbor1 = runn_cell;
				}
			}
		}
	}

	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		unsigned idnode1 = this->cells[i].vertex[1].get_ident();
		unsigned idnode2 = this->cells[i].vertex[2].get_ident();

		cell_2D *curr_cell = &this->cells[i];

		for (unsigned j = 0; j < msh_reader.nbelm; j++)
		{
			cell_2D *runn_cell = &this->cells[j];
			if (curr_cell != runn_cell) {
				unsigned cnt = 0;
				for (unsigned t = 0; t < 4; t++)
				{
					if (idnode1 == runn_cell->vertex[t].get_ident()) cnt = cnt + 1;
					if (idnode2 == runn_cell->vertex[t].get_ident()) cnt = cnt + 1;
				}
				if (cnt == 2)
				{
					this->cells[i].neighbor2 = runn_cell;
				}
			}
		}
	}

	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		unsigned idnode1 = this->cells[i].vertex[2].get_ident();
		unsigned idnode2 = this->cells[i].vertex[3].get_ident();

		cell_2D *curr_cell = &this->cells[i];

		for (unsigned j = 0; j < msh_reader.nbelm; j++)
		{
			cell_2D *runn_cell = &this->cells[j];
			if (curr_cell != runn_cell) {
				unsigned cnt = 0;
				for (unsigned t = 0; t < 4; t++)
				{
					if (idnode1 == runn_cell->vertex[t].get_ident()) cnt = cnt + 1;
					if (idnode2 == runn_cell->vertex[t].get_ident()) cnt = cnt + 1;
				}
				if (cnt == 2)
				{
					this->cells[i].neighbor3 = runn_cell;
				}
			}
		}

	}

	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		unsigned idnode1 = this->cells[i].vertex[3].get_ident();
		unsigned idnode2 = this->cells[i].vertex[0].get_ident();

		cell_2D *curr_cell = &this->cells[i];

		for (unsigned j = 0; j < msh_reader.nbelm; j++)
		{
			cell_2D *runn_cell = &this->cells[j];
			if (curr_cell != runn_cell) {
				unsigned cnt = 0;
				for (unsigned t = 0; t < 4; t++)
				{
					if (idnode1 == runn_cell->vertex[t].get_ident()) cnt = cnt + 1;
					if (idnode2 == runn_cell->vertex[t].get_ident()) cnt = cnt + 1;
				}
				if (cnt == 2)
				{
					this->cells[i].neighbor4 = runn_cell;
				}
			}
		}

	}
}

void list_cell_2D::write_vtk()
{
	string str;
	str = msh_reader.fname;
	str = msh_reader.fname + ".vtk";
	ofstream outfile(str);
	outfile.setf(ios::fixed, ios::floatfield);
	outfile.precision(10);
	outfile << "# vtk DataFile Version 2.0" << endl;
	outfile << "VTK Format for unstructured grid" << endl;
	outfile << "ASCII" << endl;
	outfile << "DATASET POLYDATA" << endl;
	outfile << "POINTS " << msh_reader.nbnode << " float" << endl;

	for (unsigned i = 0; i < msh_reader.nbnode; i++)
	{
		outfile << setw(15) << msh_reader.coord_nodes[i].get_x() << " " << setw(15) << msh_reader.coord_nodes[i].get_y() << " " << setw(15) << 0.0f << " " << endl;
	}

	outfile << "POLYGONS " << msh_reader.nbelm << " " << 5 * msh_reader.nbelm << endl;

	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		outfile << 4 << " " << msh_reader.id_nodes[i].id_node[5] - 1 << " " << msh_reader.id_nodes[i].id_node[6] - 1 << " " << msh_reader.id_nodes[i].id_node[7] - 1 << " " << msh_reader.id_nodes[i].id_node[8] - 1 << endl;
	}

	outfile << "CELL_DATA " << msh_reader.nbelm << endl;
	outfile << "SCALARS CELL_IDENT integer 1" << endl;
	outfile << "LOOKUP_TABLE default " << endl;

	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		outfile << this->cells[i].ident << endl;
	}

	outfile << "SCALARS NEIGHBOR1 integer 1" << endl;
	outfile << "LOOKUP_TABLE default " << endl;
	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		cell_2D *curr_cell = this->cells[i].neighbor1;
		if (curr_cell != nullptr)
		{
			outfile << curr_cell->ident << endl;
		}
		else
		{
			outfile << -1 << endl;
		}
	}

	outfile << "SCALARS NEIGHBOR2 integer 1" << endl;
	outfile << "LOOKUP_TABLE default " << endl;
	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		cell_2D *curr_cell = this->cells[i].neighbor2;
		if (curr_cell != nullptr)
		{
			outfile << curr_cell->ident << endl;
		}
		else
		{
			outfile << -1 << endl;
		}
	}

	outfile << "SCALARS NEIGHBOR3 integer 1" << endl;
	outfile << "LOOKUP_TABLE default " << endl;
	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		cell_2D *curr_cell = this->cells[i].neighbor3;
		if (curr_cell != nullptr)
		{
			outfile << curr_cell->ident << endl;
		}
		else
		{
			outfile << -1 << endl;
		}
	}

	outfile << "SCALARS NEIGHBOR4 integer 1" << endl;
	outfile << "LOOKUP_TABLE default " << endl;
	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		cell_2D *curr_cell = this->cells[i].neighbor4;
		if (curr_cell != nullptr)
		{
			outfile << curr_cell->ident << endl;
		}
		else
		{
			outfile << -1 << endl;
		}
	}

	outfile.close();
}

#endif /* FVMMESH2D_H */

