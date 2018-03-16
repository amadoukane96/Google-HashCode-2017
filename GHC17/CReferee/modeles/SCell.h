#pragma once
#include <istream>
#include "SPoint.h"
struct SCell {
	///-------------------------------------------------------------------------------------------------
	/// @enum	EType
	///
	/// @brief	�num�ration qui repr�sente les diff�rentes types de cellule
	///-------------------------------------------------------------------------------------------------

	enum EType : char {
		/// @brief	mur peut �tre connecter au backbone.
		WALL = '#',
		/// @brief	cellule vide, on peut y placer un routeur, et la connecter au routeur
		VOID = '-',
		/// @brief	cellule � couvrir.
		TARGET = '.'
	} type;
	/// @brief	nombre de routeur diff�rent qui la couvre.
	unsigned int nbCovered = 0;
	SPoint pos;
	inline bool isEmpty() { return type == VOID; }
	inline bool isWall() { return type == WALL; }
	inline bool isTarget() { return type == TARGET; }
	bool operator==(const SCell& c) { c.pos == pos; }
	bool operator<(const SCell& c) { return pos < c.pos; }
};
std::istream& operator>>(std::istream& in, SCell::EType& t);
