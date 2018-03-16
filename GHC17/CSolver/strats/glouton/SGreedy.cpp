#include "SGreedy.h"
#include "../steinerTree.h"
#include "CReferee.h"
#include <time.h>
#define max(a, b) (a > b) ? a : b

SPoint SGreedy::findBestSpot(bool & ok)
{
	SPoint best = {};
	std::pair<int, int> max = {0, 0};
	std::vector<std::pair<SPoint, int>> bests = {};

	for (int i = 0; i < in->getNbRows(); i++) {
		for (int j = 0; j < in->getNbCols(); j++) {

			if (!rtr_c[i][j].second && in->getCell(SPoint(i, j)).isTarget()){
				if (rtr_c[i][j].first > max.first){
					best = SPoint(i, j);
					max = { rtr_c[i][j].first, SPoint(i, j).distance(in->getBackbone()) };
				}
			}
		}
	}

	ok = max.first != 0;
	return best;
}

CSolution SGreedy::operator()(CInput * in)
{

	//initialisation
	this->in = in;
	rtr_c = { (unsigned int)in->getNbRows(), std::vector<std::pair<int, bool>>((unsigned int)in->getNbCols(), std::pair<int, bool>(0, false)) };
	CReferee ref(in, &sln);
	SPoint new_r(0, 0);


	for (int i = 0; i < in->getNbRows(); i++) {
		for (int j = 0; j < in->getNbCols(); j++) {
			new_r = { i, j};

			if(in->getCell(new_r).isTarget()) {
			
				rtr_c[i][j].first = ref.router_range(new_r);				
			}
			
		}
	}

	//premiere boucle, on place le plus possible de routers enfin de couvrir l'ensemble des points sur la mp
	//on ne se souci pas du cout des cables.

	bool continu = true;
	while (ref.cost() + in->getRouterPrice() < in->getBudget())
	{
	
		//on trouve le point qui permet de couvrir le plus de points
		SPoint best = findBestSpot(continu);

		//si y n'a pas on arrête.
		if (!continu) {
			break;
		}
		//on place un router à ce point
		rtr_c[best.row][best.col].second = true;
		sln.routers.push_back(best);

		//on prend en compte le placement de ce router
		int i = 0;
		ref.couverture_router(best);

		//on mets à jours le nombre de points couvert par les points dans sont entourage.
		for (int row = max(0, best.row - 2 * in->getRouterRange()); row <= min(best.row + 2 * in->getRouterRange(), in->getNbRows() - 1); row++) {
			for (int col = max(0, best.col - 2 * in->getRouterRange()); col <= min(best.col + 2 * in->getRouterRange(), in->getNbRows() - 1); col++) {
				if (in->getCell(SPoint(row, col)).isTarget() && !rtr_c[row][col].second) {
					rtr_c[row][col].first = ref.router_range(SPoint(row, col));
				}
			}
		}

	}

	//on connecte les routers placés au backbone:
	std::vector<SPoint> noeud = sln.routers;
	noeud.insert(noeud.begin(), in->getBackbone());

	sln.connexions = Takahashi_steiner_tree(in, noeud, 1, in->getBackbone());

	//si le coût totale dépasse le budget on enlève des routers jusqu’à être en dessous du budget.
	
	/*  
	note le tableau des routers est déjà trié par ordre décroissant en fonction de 
	la taille de couverture de chacun
	*/
	while (ref.cost() > in->getBudget()) {
		sln.routers.pop_back();
		noeud.pop_back();

		sln.connexions = Takahashi_steiner_tree(in, noeud, 1, in->getBackbone());
	}

	//On réarrange les connections pour que les conditions de validation soit satisfait.
	sln.arranger(in->getBackbone());

	return sln;
}
