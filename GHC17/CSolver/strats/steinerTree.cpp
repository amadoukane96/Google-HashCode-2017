#include "steinerTree.h"
#include "modeles/SCell.h"
#include <algorithm>
#include <map>

std::vector<SPoint> terms = {};
std::vector<SPoint> str = {};

std::vector<SPoint> shortestPath(CInput* map, SPoint start, SPoint end, std::vector<SPoint> paths, SPoint ignore)
{
	std::vector<SPoint> path = {};

	int drow = end.row - start.row;
	int dcol = end.col - start.col;

	int i = (drow < 0) ? -1 : 1;
	int j = (dcol < 0) ? -1 : 1;
	//std::cout << SPoint(drow, dcol) << std::endl;

	while (!(start == end)) {
		std::vector<SPoint> dir = {};

		if (start.row != end.row && end.col != start.col) {
			dir.push_back(SPoint(i, j) + start);
		}

		if (start.row != end.row) {
			dir.push_back(SPoint(i, 0) + start);
		}
		if (end.col != start.col) {
			dir.push_back(SPoint(0, j) + start);
		}

		bool stop = false;
		int i = 0;
		bool done = false;
		///*
		//while(i < dir.size() && !stop) {
		//	/*
		//	if (std::find(paths.begin(), paths.end(), dir[i]) != paths.end()) {
		//		dir[0] = dir[i];
		//		stop = true;
		//	}
		//	*/
		//	if (!stop && !done && !map->getCell(dir[i]).isEmpty()) {
		//		dir[0] = dir[i];
		//		done = true;
		//	}
		//	
		//	i++;
		//}
		//*/

		start = dir[0];
		if (std::find(paths.begin(), paths.end(), start) == paths.end() && !(ignore == start)) {
			path.push_back(start);
		}
		//std::cout << "end !moved" << std::endl;

	}

	//std::cout << "added: " << stree.size() - d << std::endl;
	return path;
}

/*
void Takahashi_steiner_tree_acc(CInput* map, SPoint terminal, SPoint ignore) {
//std::cout << "nb nd = " << terminals.size() << std::endl;


int min_d = std::numeric_limits<int>::max();
SPoint min_s(-1, -1);
int i = 0;
int min_i;
SPoint to = {};

for (auto p : terms) {
int d_i = p.distance(terminal);

if (d_i < min_d) {
min_d = d_i;
min_s = p;
min_i = i;
}

i++;

}

//std::cout << "closeset node found to " << added_l.back() << " :"  << min_s << std::endl;

std::vector<SPoint> path = shortestPath(map, terminal, min_s, str, ignore);
//std::cout << "path length = " << path.size() << std::endl;

str.insert(stree.end(), path.begin(), path.end());

added_l.push_back(min_s);
isAdded[min_i] = true;
//std::coud << "connexions size " << stree.size() << std::endl;

strees.push_back(stree);

//std::cout << "finished lets sor" << std::endl;
auto min_it = std::min_element(std::begin(strees), std::end(strees), [](const auto& s1, const auto& s2) {return s1.size() < s2.size(); });
//std::cout << "finished sort" << std::endl;

std::vector<SPoint> min_stree = *min_it;

std::cout << "finished" << std::endl;
/*
SPoint min_s;
int min_d = std::numeric_limits<int>::max();

std::vector<SPoint> path = shortestPath(map, ignore, min_stree[0], min_stree, ignore);

min_stree.insert(min_stree.begin(), path.begin(), path.end());


}
*/

//inspir� de l'article https://bmcbioinformatics.biomedcentral.com/articles/10.1186/1471-2105-14-144#Equ1

std::vector<SPoint> Takahashi_steiner_tree(CInput* map, std::vector<SPoint> terminals, unsigned int loops, SPoint ignore)
{

	//std::cout << "nb nd = " << terminals.size() << std::endl;
	terminals.push_back(ignore);
	std::random_shuffle(terminals.begin(), terminals.end());
	std::vector<std::vector<SPoint>> strees = {};
	std::vector<int> pos_back_bone = {};
	int t;

	for (unsigned int r = 0; r < loops; r++) {
		std::vector<SPoint> stree;
		if (!(terminals[r] == ignore)) {
			stree.push_back(terminals[r]);
		}

		std::vector<bool> isAdded(terminals.size(), false);
		isAdded[r] = true;
		std::list<SPoint> added_l = { terminals[r] };

		while (added_l.size() < terminals.size()) {
			//std::cout << "iteration t " << added_l.size() << std::endl;

			int min_d = std::numeric_limits<int>::max();
			SPoint min_s(-1, -1);
			int i = 0;
			int min_i;
			SPoint to = {};
			for (auto p : terminals) {
				if (!isAdded[i]) {
					for (SPoint tr : added_l) {
						int d_i = p.distance(tr);

						if (d_i < min_d) {
							min_d = d_i;
							min_s = p;
							min_i = i;
							to = tr;
						}
					}

				}
				i++;

			}

			//std::cout << "closeset node found to " << added_l.back() << " :"  << min_s << std::endl;

			std::vector<SPoint> path = shortestPath(map, to, min_s, stree, ignore);
			//std::cout << "path length = " << path.size() << std::endl;
			if (to == ignore) {
				pos_back_bone.push_back(stree.size());
			}
			stree.insert(stree.end(), path.begin(), path.end());

			added_l.push_back(min_s);
			isAdded[min_i] = true;
			//std::cout << "connexions size " << stree.size() << std::endl;

		}
		strees.push_back(stree);
	}

	//std::cout << "finished lets sor" << std::endl;
	auto min_it = std::min_element(std::begin(strees), std::end(strees), [](const auto& s1, const auto& s2) {return s1.size() < s2.size(); });
	//std::cout << "finished sort" << std::endl;

	std::vector<SPoint> min_stree = *min_it;

	//std::cout << "finished" << std::endl;
	/*
	SPoint min_s;
	int min_d = std::numeric_limits<int>::max();

	std::vector<SPoint> path = shortestPath(map, ignore, min_stree[0], min_stree, ignore);

	min_stree.insert(min_stree.begin(), path.begin(), path.end());
	*/

	return min_stree;
}