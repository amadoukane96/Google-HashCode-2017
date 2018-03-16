#pragma once
#include "modeles/CInput.h"
#include "modeles/CSolution.h"
#include "modeles/SPoint.h"
#include <map>

class SGreedy
{
private:
	/*
	une case de ce tableau-2d contient deux informations: 
		_le nombre de points couvert si on plaçait un router dans celle-ci;
		_si un router a était placer dans cette case.
	*/
	std::vector<std::vector<std::pair<int, bool>>> rtr_c;
	CInput* in;
	CSolution sln = {};
public:

	inline SGreedy() {};
	//trouve le meilleur endroit ou placer un nouveau router, si tout les points sont couverts ok = false
	SPoint findBestSpot(bool &ok);
	CSolution operator()(CInput* in);
};