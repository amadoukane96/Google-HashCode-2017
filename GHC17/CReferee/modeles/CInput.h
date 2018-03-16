#pragma once
#include "SPoint.h"
#include <ostream>
#include <vector>
#include <list>
#include "SCell.h"

///-------------------------------------------------------------------------------------------------
/// @class	CInput
///
/// @brief	une entrée est extraite à partir d'un fichier text, 
/// 		cette class permet de modéliser les différents attributs de celle-ci
///
/// @date	10/11/2017
///-------------------------------------------------------------------------------------------------

class CInput
{
private:

	/// @brief	le nombre de lignes dans la map.
	unsigned int nbRows = 0;
	/// @brief	le nombre de colonnes dans la map.
	unsigned int nbCols = 0;
	/// @brief	le budget à ne pas dépasser: nbRouter * PrixRouter + nbCelluleConnecté * Prix <= budget.
	unsigned int budget;
	/// @brief	le prix d'un router.
	unsigned int routerPrice;
	/// @brief	le prix qu'il faut payer pour connecter une cellule au backbone.
	unsigned int backbonePrice;
	/// @brief	le rayon du carré de points couvert par un router.
	unsigned int routerRange;
	/// @brief	les coordonnés du SPoint d'entré (backbone).
	SPoint backbone;

	///-------------------------------------------------------------------------------------------------
	/// @struct	SCell
	///
	/// @brief	Décrit une case de la map
	///
	/// @date	13/11/2017
	///-------------------------------------------------------------------------------------------------

	/// @brief	tableaux 2-d stockant la map, chaque case peut être un mur, vide, cellule. 
	SCell** map = nullptr;
public:

	///-------------------------------------------------------------------------------------------------
	/// @fn	CInput::CInput();
	///
	/// @brief	Constructeur vide
	///
	/// @date	10/11/2017
	///-------------------------------------------------------------------------------------------------

	CInput();

	///-------------------------------------------------------------------------------------------------
	/// @fn	CInput::CInput(const char* filename_in);
	///
	/// @brief	construit un CInput à partir d'un fichier texte (voir format à respecter).
	///
	/// @date	11/11/2017
	///
	/// @param	filename_in	le nom du fichier.
	///-------------------------------------------------------------------------------------------------

	CInput(const char* filename_in);

	///-------------------------------------------------------------------------------------------------
	/// @fn	CInput::CInput(const CInput& c);
	///
	/// @brief	constructor de Copie
	///
	/// @date	10/11/2017
	///
	/// @param c un CInput à copier.
	///-------------------------------------------------------------------------------------------------

	CInput(const CInput& c);

	///-------------------------------------------------------------------------------------------------
	/// @fn	CInput::CInput(CInput&& c);
	///
	/// @brief	constructeur par déplacement
	///
	/// @date	10/11/2017
	///
	/// @param c un CInput à déplacer.
	///-------------------------------------------------------------------------------------------------

	CInput(CInput&& c);

	///-------------------------------------------------------------------------------------------------
	/// @fn	CInput::~CInput();
	///
	/// @brief	Destructeur
	///
	/// @date	10/11/2017
	///-------------------------------------------------------------------------------------------------

	virtual ~CInput();

	///-------------------------------------------------------------------------------------------------
	/// @fn	CInput& CInput::operator=(const CInput& c);
	///
	/// @brief	Assignment operator
	///
	/// @date	10/11/2017
	///
	/// @param	c	A CInput to process.
	///
	/// @return	A shallow copy of this object.
	///-------------------------------------------------------------------------------------------------

	CInput& operator=(const CInput& c);

	///-------------------------------------------------------------------------------------------------
	/// @fn	CInput& CInput::operator=(CInput&& c);
	///
	/// @brief	Move assignment operator
	///
	/// @date	10/11/2017
	///
	/// @param [in,out]	c	A CInput to process.
	///
	/// @return	A shallow copy of this object.
	///-------------------------------------------------------------------------------------------------

	CInput& operator=(CInput&& c);


	/*GETTER*/

	inline int getNbRows() { return nbRows; }
	inline int getNbCols() { return nbCols; }
	inline int getRouterRange()const { return routerRange; }
	inline int getRouterPrice()const { return routerPrice; }
	inline int getBackbonePrice()const { return backbonePrice; }
	inline SPoint getBackbone() const{ return backbone; }
	inline int getBudget()const { return budget; }

	inline SCell& getCell(SPoint p)const {return map[p.row][p.col];}
	inline SCell getCell(SPoint p)  { return map[p.row][p.col]; }
	inline SCell& getCell(int r, int col) const {return map[r][col];}


	std::list<SCell> getNeighbors(SPoint pos);
	std::list<SPoint> getNeighborsPos(SPoint pos);


friend std::istream& operator>>(std::istream& in, CInput& c);
friend std::ostream& operator<<(std::ostream& o, const CInput& c);
friend class CReferee;
friend class SRandom;

};

std::istream& operator>>(std::istream& in, CInput& c);
//only for debugging purposess  
std::ostream& operator<<(std::ostream& o, const CInput& c);


inline int min(int a, int b) {
	int m = (a < b) ? a : b;
	return m;
}
