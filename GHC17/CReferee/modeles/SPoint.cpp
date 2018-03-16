#include "SPoint.h"
#include <unordered_map>
#include <random>


std::ostream & operator<<(std::ostream & o, const SPoint & p)
{
	o << p.row << " " << p.col;
	return o;
}

bool SPoint::operator==(const SPoint & p) const
{
	return p.row == row && p.col == col;
}

std::list<SPoint> SPoint::getNeighbors()
{

	std::list<SPoint> neighbours = {};

	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (dx != 0 || dy != 0) {
				SPoint fp(row + dx, col + dy);
				neighbours.push_back(fp);
			}
		}
	}

	//std::cout << "finished nbrg!" << std::endl;
	return neighbours;
	
}

bool SPoint::isNeighbor(SPoint point)
{
	for (SPoint neighbor : getNeighbors()) {
		if (neighbor == point) { return true; }
	}
	return false;
}

SPoint SPoint::bruiter(int range, int N, int M)
{
	int min_r = maxm(0, row - range);

	int max_r = minm(N, row + range);

	int min_c = maxm(0, col - range);

	int max_c = minm(M, col + range);

	//rand() % (max - min + 1) + min
	int r_r = rand() % (max_r - min_r + 1) + min_r; // uniform, unbiased
	int c_r = rand() % (max_c - min_c + 1) + min_c;

	return SPoint(r_r, c_r);
}

