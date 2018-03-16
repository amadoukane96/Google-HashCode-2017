#include "CReferee.h"
#include <set>
#include <list>
#include <cmath>
#define max(a, b) (a > b) ? a : b
#define ADD 1
#define DELETE -1

CReferee::CReferee() : input(nullptr) {}

CReferee::CReferee(const CReferee & ref) : CReferee(ref.input) {}

CReferee::CReferee(CInput * in) : input(in) {}

CReferee& CReferee::operator=(const CReferee & ref)
{
	input = ref.input;
	return *this;
}

unsigned int CReferee::cost() const {
	unsigned int cost = 0;
	cost = sln->nbRouters() * input->getRouterPrice() + sln->nbConnectedCells() * input->getBackbonePrice();
	return cost;
}

//Verifie qu'il y a un chemin qui lie chaque router au backbone et que le graphe des connexions est connexe et connecté au backbone
bool CReferee::isConnexe() {
	int nbConnectedRouters = 0;
	std::vector<SPoint> connectedPoints; //Set contenant tous les points vérifiés et validés
	//On parcours les autres points des connexions filiaires pour s'assurer que le graphe est connexe et connecté au backbone
	for (std::vector<int>::size_type i = 0; i != sln->connexions.size(); i++) {
		bool wireOk = false; //booléen stockant si le point courant est bien connecté au backbone

		//Si le point courant est bien voisin au point précedent dans le vecteur des connexions
		if (i>=1 && sln->connexions[i].isNeighbor(sln->connexions[i-1])) {
			connectedPoints.push_back(sln->connexions[i]);
			wireOk = true;
		}
		//Ou si le point courant est voisin à un des points déjà connectés au backbone
		if (!wireOk) {
			for (SPoint connectedPoint : connectedPoints) {
				if (sln->connexions[i].isNeighbor(connectedPoint)) {
					connectedPoints.push_back(sln->connexions[i]); //Ajout du point courant aux points vérifiés connectés au backbone
					wireOk = true;
					break;
				}
				if (wireOk) {
					break;
				}
			}
		}
		//Si le point courant est voisin au backbone
		if (sln->connexions[i].isNeighbor(input->backbone)) {
			connectedPoints.push_back(sln->connexions[i]);
			wireOk = true;
		}

		if (!wireOk) { //Si le point courant n'est finalement pas connecté (ni directement ni indirectement) au backbone
			std::cout << "Pas connecté " << std::endl;
			return false;
		}
		else { 
			//Parcours des routers de la solution
			//S'il y a un router sur le point courant on incrémente le compteur des routers connectés
			if (std::find(sln->routers.begin(), sln->routers.end(), sln->connexions[i]) != sln->routers.end()) {
				nbConnectedRouters++; 
			}
		}
	}
	//Compare le nombre de router bien connectés au nombre de router de la solution
	if (nbConnectedRouters == sln->routers.size()) {
		return true;
	}
	else {
		return false;
	}
}

unsigned int CReferee::score()
{

	unsigned int score = 0;
	covered = 0;

	//si la solution est valide
	if (isConnexe()) {
		//on calcul le nombre de points couverts
		for (SPoint rtr : sln->routers) {
			couverture_router(rtr);
		}
		score = 1000 * covered + input->getBudget() - cost();
	}

	return score;
}

int CReferee::move_router(SPoint old_r, SPoint new_r)
{
	if (input->getCell(new_r).isWall()) {
		return false;
	}

	remove_router(old_r);

	//sln->routers[id_r] = new_r;
	return couverture_router(new_r).size();
}

void CReferee::remove_router(SPoint rtr)
{
	for (SPoint trg : couverture_router(rtr)) {
		nbCovered[trg.row][trg.col] -= 2;
		if (nbCovered[trg.row][trg.col] == 0) {
			covered -= 2;
		}
	}
}


int CReferee::router_range(SPoint rtr)
{

	int cv_o = covered;
	auto cv = couverture_router(rtr);
	int cv_n = 0;

	for (SPoint trg : cv) {
		//std::cout << nbCovered[trg.row][trg.col] << std::endl;

		nbCovered[trg.row][trg.col]--;
		if (nbCovered[trg.row][trg.col] == 0) {
			covered--;
			cv_n++;
		}
	}

	//std::cout << rtr <<" cv_o = " << cv_o << " cv_n = " << covered << std::endl;
	return cv_n;
}

std::list<SPoint> CReferee::couverture_router(SPoint rtr)
{
	int R = input->getRouterRange();

	SPoint left_up(max(0, rtr.row - R), max(0, rtr.col - R));

	SPoint right_up(left_up.row, min(input->getNbCols() - 1, rtr.col + R));

	SPoint left_down(min(input->getNbRows() - 1, rtr.row + R), left_up.col);
	SPoint right_down(left_down.row, right_up.col);

	std::vector<SPoint> squares = { left_up, right_up, left_down, right_down };


	std::list<SPoint> couverture = {};

	for (SPoint corner : squares) {
		int di = (corner.row - rtr.row > 0) ? 1 : -1;
		int dj = (corner.col - rtr.col > 0) ? 1 : -1;

		//std::cout << corner << std::endl;

		for (int row = rtr.row; di*(corner.row - row) >= 0; row += di) {
			for (int col = rtr.col; dj*(corner.col - col) >= 0; col += dj) {
				if (row != rtr.row && nbCovered[row - di][col] == 0) {
					break;
				}
				if (input->getCell(SPoint(row, col)).isWall()) {
					break;
				}
				if (input->getCell(SPoint(row, col)).isTarget()) {
					if (row != rtr.row && col != rtr.col) {
						couverture.push_back(SPoint(row, col));
					}

					if (nbCovered[row][col] == 0) {
						covered++;
					}
					nbCovered[row][col]++;
				}
			}
		}
	}

	for (int col = rtr.col; col <= right_up.col; col++) {
		if (!input->getCell(SPoint(rtr.row, col)).isWall()) {

			if (col != rtr.col) {
				nbCovered[rtr.row][col]--;

				couverture.push_back(SPoint(rtr.row, col));
			}
		}
		else {
			break;
		}
	}
	for (int col = rtr.col; col >= left_up.col; col--) {
		if (!input->getCell(SPoint(rtr.row, col)).isWall()) {
			if (col != rtr.col) {
				nbCovered[rtr.row][col]--;

				couverture.push_back(SPoint(rtr.row, col));
			}
		}
		else {
			break;
		}
	}

	for (int row = rtr.row; row <= left_down.row; row++) {
		if (!input->getCell(SPoint(row, rtr.col)).isWall()) {
			if (row != rtr.row) {
				nbCovered[row][rtr.col]--;

				couverture.push_back(SPoint(row, rtr.col));
			}
		}
		else {
			break;
		}
	}
	for (int row = rtr.row; row >= left_up.row; row--) {
		if (!input->getCell(SPoint(row, rtr.col)).isWall()) {
			if (row != rtr.row) {
				nbCovered[row][rtr.col]--;

				couverture.push_back(SPoint(row, rtr.col));
			}
		}
		else {
			break;
		}
	}
	couverture.push_back(rtr);
	nbCovered[rtr.row][rtr.col] -= 3;
	return couverture;
}