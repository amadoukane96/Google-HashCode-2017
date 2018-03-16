#pragma once
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include "SPoint.h"
#include <istream>

class CSolution
{

public:
	unsigned int score = 0;
	unsigned int cost = 0;

	std::vector<SPoint> routers; //Vecteur des coordonnées des routeurs de la solution
	std::vector<SPoint> connexions; //Vecteur des points connectés au backcbone nécessaires pour brancher nos routeurs

	CSolution();
	CSolution(const char* filename);

	inline void arranger(SPoint b) { std::vector<SPoint> r = {}; arrangerConnexions(b, r); connexions = r; }
	void arrangerConnexions(SPoint backbone, std::vector<SPoint>& res);

	//inline void addRouter(SPoint router) { routers.insert(router); }; //Ajoute un routeur à la solution
	//inline void connectPoint(SPoint SPoint) { connexions.insert(SPoint); } //Ajouter une connexion filiaire sur un SPoint passé en paramètre
	//inline void addPath(std::set<SPoint> points) { for (SPoint p : points) { connexions.insert(p); } } //Ajouter une connexion filiaire sur tous les points du vecteur passé en paramètre
	inline unsigned int nbRouters() const{ return routers.size(); }
	inline unsigned int nbConnectedCells()const { return connexions.size(); }

	virtual ~CSolution();
	friend std::istream& operator>>(std::istream& in, CSolution& sln);
	friend std::ostream& operator<<(std::ostream& out, const CSolution& sln);
	friend class CReferee;
	friend class SGreedy;
};	

std::istream& operator>>(std::istream& in, CSolution& sln);
std::ostream& operator<<(std::ostream& out, const CSolution& sln);