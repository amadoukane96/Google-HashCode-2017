#include "CInput.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include "SPoint.h"

CInput::CInput(){}

CInput::CInput(const char * filename_in)
{
	std::ifstream file_in;
	file_in.open(filename_in);

	if (file_in.good()) {
		file_in >> *this;
	}
	//SPoint 


	file_in.close();
}

CInput::CInput(const CInput & c) : nbCols(c.nbCols), nbRows(c.nbRows), budget(c.budget),
routerPrice(c.routerPrice), backbonePrice(c.backbonePrice),
routerRange(c.routerRange), backbone(c.backbone)
{
	//copie de la map
	map = new SCell*[nbRows];
	for (unsigned int r = 0; r < nbRows; r++) {
		map[r] = new SCell[nbCols];
		for (unsigned int col = 0; col < nbCols; col++) {
			map[r][col] = c.map[r][col];
		}
	}
}

CInput::CInput(CInput && c): nbCols(c.nbCols), nbRows(c.nbRows), budget(c.budget),
routerPrice(c.routerPrice), backbonePrice(c.backbonePrice),
routerRange(c.routerRange), backbone(c.backbone)
{
	map = c.map;
	c.map = nullptr;
}

CInput::~CInput()
{
	for (unsigned int r = 0; r < nbRows; r++) {
		delete[] map[r];
	}

	delete[] map;
}

CInput& CInput::operator=(const CInput & c)
{
	nbCols = c.nbCols;
	nbRows = c.nbRows;
	budget = c.budget;
	routerPrice = c.routerPrice;
	backbonePrice = c.backbonePrice;
	routerRange = c.routerRange;
	backbone = c.backbone;

	//copie de la map
	map = new SCell*[nbRows];
	for (unsigned int r = 0; r < nbRows; r++) {
		map[r] = new SCell[nbCols];
		for (unsigned int col = 0; col < nbCols; col++) {
			map[r][col] = c.map[r][col];
		}
	}

	return *this;
}

CInput & CInput::operator=(CInput && c)
{
	nbCols = c.nbCols;
	nbRows = c.nbRows;
	budget = c.budget;
	routerPrice = c.routerPrice;
	backbonePrice = c.backbonePrice;
	routerRange = c.routerRange;
	backbone = c.backbone;
	
	map = c.map;
	c.map = nullptr;
	return *this;
}

std::list<SCell> CInput::getNeighbors(SPoint p)
{
	std::list<SCell> neighbours = {};
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (dx != 0 || dy != 0) {
				SPoint fp(p.row + dx, p.col + dy);
				if (fp.in(nbRows, nbCols)) {
					SCell tmp_c = getCell(fp);
					neighbours.push_back(tmp_c);
				}
			}
		}
	}

	return neighbours;
}

std::list<SPoint> CInput::getNeighborsPos(SPoint p)
{
	std::list<SPoint> neighbours = {};
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (dx != 0 || dy != 0) {
				SPoint fp(p.row + dx, p.col + dy);
				if (fp.in(nbRows, nbCols)) {
					neighbours.push_back(fp);
				}
			}
		}
	}

	return std::list<SPoint>();
}

/*only for test purposes*/

std::ostream & operator<<(std::ostream & o, const CInput & c)
{
	o << "dimensions: " << c.nbRows << " x " << c.nbCols << '\n';
	o << "Budget: " << c.budget << '\n';
	o << "Tarification: " << '\n';
	o << '\t' << c.routerPrice << "$/router" << '\n';
	o << '\t' << c.backbonePrice << "$/cell" << '\n';
	o << "BackBone @" << c.backbone << '\n';
	o << "router range " << c.routerRange;
	/*
	for (unsigned int r = 0; r < c.nbRows; r++) {
		o << '\n';
		for (unsigned int col = 0; col < c.nbCols; col++) {
			if (c.backbone == SPoint(r, col)) {
				o << 'b';
			}
			else {
				o << static_cast<char>(c.map[r][col].type);
			}
		}
	}
	*/
	return o;
}

std::istream& operator>>(std::istream & in, CInput & c)
{
	in >> c.nbRows >> c.nbCols >> c.routerRange;
	//la deuxième ligne
	in >> c.backbonePrice >> c.routerPrice >> c.budget;
	//la troisième indique la position du backbone
	in >> c.backbone.row >> c.backbone.col;

	c.map = new SCell*[c.nbRows];
	for (unsigned int r = 0; r < c.nbRows; r++) {
		c.map[r] = new SCell[c.nbCols];
		for (unsigned int col = 0; col < c.nbCols; col++) {
			in >> c.map[r][col].type;
			c.map[r][col].pos = { r, col };
		}
	}

	return in;
}
/*
int main() {
	CInput c("..\\..\\input\\small_town.in");
	std::cout << c << std::endl;

	std::list<SPoint> trgs = c.targetInRange(c.getBackbone());
	std::cout << "nb targets = " << trgs.size() << std::endl;

	for (int r = 0; r < c.getNbRows(); r++) {
		for (int cl = 0; cl < c.getNbCols(); cl++) {
			SPoint tmp(r, cl);
			if (tmp == c.getBackbone()) {
				std::cout << "b";
			}
			else if (std::find(trgs.begin(), trgs.end(), tmp) != trgs.end()) {
				std::cout << "T";
			}
			else {
				std::cout << static_cast<char>(c.getCell(tmp).type);
			}
		}
		std::cout << std::endl;
	}
	system("pause");

	return 0;
}
*/