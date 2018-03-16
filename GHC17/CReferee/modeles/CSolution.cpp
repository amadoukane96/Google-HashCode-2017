#include "CSolution.h"
#include <istream>
#include <fstream>


CSolution::CSolution() : routers(), connexions()
{
}

CSolution::CSolution(const char* filename)
{
	std::ifstream out;
	out.open(filename);
	out >> *this;
	out.close();
}

void CSolution::arrangerConnexions(SPoint backbone, std::vector<SPoint>& res) {


	if (res.size() < connexions.size()) {
		for (SPoint v : backbone.getNeighbors()) {
			if (std::find(res.begin(), res.end(), v) == res.end() && std::find(connexions.begin(), connexions.end(), v) != connexions.end()) {
				res.push_back(v);
				arrangerConnexions(v, res);
			}
		}
	}
}


CSolution::~CSolution()
{
}

std::istream & operator>>(std::istream & in, CSolution & sln)
{
	unsigned int N = 0;
	SPoint tmp_cell;

	in >> N;
	for (unsigned int i = 0; i < N; i++) {
		in >> tmp_cell.row >> tmp_cell.col;
		sln.connexions.push_back(tmp_cell);
	}
	unsigned int M = 0;
	in >> M;
	for (unsigned int j = 0; j < M; j++) {
		in >> tmp_cell.row >> tmp_cell.col;
		sln.routers.push_back(tmp_cell);
	}

	return in;
}

std::ostream & operator<<(std::ostream & out, const CSolution & sln)
{
	out << sln.connexions.size() << std::endl;
	for (SPoint cell: sln.connexions) {
		out << cell << std::endl;
	}
	out << sln.routers.size() << std::endl;
	for (SPoint cell: sln.routers) {
		out << cell << std::endl;;
	}

	return out;
}
