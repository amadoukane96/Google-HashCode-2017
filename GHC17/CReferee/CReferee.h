#pragma once

#include "modeles/CSolution.h"
#include "modeles/CInput.h"
#include "modeles/SPoint.h"
#include <vector>
#include <set>
///-------------------------------------------------------------------------------------------------
/// @class	CReferee
///
/// @brief	Juge Arbitre
///
/// @author	MOTALY
/// @date	11/11/2017
///-------------------------------------------------------------------------------------------------

class CReferee
{
private:
	CInput* input;
	CSolution* sln;

	std::vector<std::vector<int>> nbCovered;
public:
	unsigned int covered;

	inline CReferee(CInput* in, CSolution* s) : input(in), sln(s) {
		init();
	}

	///-------------------------------------------------------------------------------------------------
	/// @fn	CReferee::CReferee();
	///
	/// @brief	Default constructor
	///
	/// @date	11/11/2017
	///-------------------------------------------------------------------------------------------------

	CReferee();

	///-------------------------------------------------------------------------------------------------
	/// @fn	CReferee::CReferee(const CReferee& ref);
	///
	/// @brief	Copy constructor
	///
	/// @date	11/11/2017
	///
	/// @param	ref	The reference.
	///-------------------------------------------------------------------------------------------------

	CReferee(const CReferee& ref);

	///-------------------------------------------------------------------------------------------------
	/// @fn	CReferee::CReferee(CInput* in);
	///
	/// @brief	Constructeur
	///
	/// @date	11/11/2017
	///
	/// @param Un pointer vers CInput.
	///-------------------------------------------------------------------------------------------------

	CReferee(CInput* in);

	///-------------------------------------------------------------------------------------------------
	/// @fn	CReferee& CReferee::operator=(const CReferee& ref);
	///
	/// @brief	Assignment operator
	///
	/// @date	11/11/2017
	///
	/// @param	ref	The reference.
	///
	/// @return	A shallow copy of this object.
	///-------------------------------------------------------------------------------------------------

	CReferee& operator=(const CReferee& ref);

	///-------------------------------------------------------------------------------------------------
	/// @fn	CReferee::~CReferee();
	///
	/// @brief	Destructeurr
	///
	/// @date	11/11/2017
	///-------------------------------------------------------------------------------------------------

	inline virtual ~CReferee() {}

	///-------------------------------------------------------------------------------------------------
	/// @fn	unsigned int CReferee::score(const CSolution& sln, bool& valide);
	///
	/// @brief	Calcule le score d'un Solution. 0 si elle n'est pas valide.
	///
	/// @author	MOTALY
	///
	/// @param 		   	sln   	Une Solution à verifier.
	///
	/// @return	le score.
	///-------------------------------------------------------------------------------------------------

	unsigned int cost() const;

//	static unsigned int cost(const CSolution& sln) const;

	unsigned int score();
	
	unsigned inline int score_t() { return covered * 1000 + input->getBudget() - cost(); }

	int move_router(SPoint old_r, SPoint new_r);
	void remove_router(SPoint rtr);

	int router_range(SPoint rtr);
	std::list<SPoint> couverture_router(SPoint rtr);


	inline void init(){
		covered = 0;
		nbCovered = { input->nbRows, std::vector<int>(input->getNbCols(), 0) };
	}
	CSolution inline getSln() { return *sln; }
	bool CReferee::isConnexe();

};