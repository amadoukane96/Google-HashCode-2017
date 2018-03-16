#pragma once
#include <iostream>
#include <set>
#include <list>
#include <random>

inline int& maxm(int a, int b) { int c = (a > b) ? a : b; return c; }
inline int& minm(int a, int b) { int c = (a < b) ? a : b; return c; }

struct SPoint {
	int row, col;

	inline SPoint() : row(0), col(0) {}
	inline SPoint( int r,  int c): row(r), col(c){}
	inline SPoint(unsigned int r, unsigned int c) : row(r), col(c) {}
	SPoint(const SPoint&) = default;
	SPoint& operator=(const SPoint&) = default;

	inline SPoint& min(SPoint p) { SPoint m = { minm(row, p.row), col = minm(col, p.col) }; return m; }

	bool operator==(const SPoint& p) const;
	inline bool operator!=(const SPoint& p) const {
		return !(*this == p);
	}

	inline SPoint& operator-(int k) { row -= k; col -= k; return *this; }
	inline SPoint& operator+(int k) { return operator-(-1 * k); }
	inline SPoint& operator-=(int k) { row -= k; col -= k; return *this; }

	inline SPoint& operator+(const SPoint& p) { row += p.row; col += p.col; return *this; }
	inline bool operator<(const SPoint& p) const {
		return (row < p.row) && (col < p.col);
	}
	inline bool operator>(const SPoint& p) const {
		return (row > p.row) && (col > p.col);
	}
	inline bool operator<=(const SPoint& p) const {
		return *this < p || *this == p;
	}
	inline bool operator>=(const SPoint& p) const {
		return *this > p || *this == p;
	}
	inline unsigned int distance(SPoint p)const  {return maxm(abs((int)(row - p.row)), abs((int)(col - p.col)));}
	std::list<SPoint> getNeighbors();
	bool isNeighbor(SPoint point);
	inline bool in(unsigned int N, unsigned int M) { return row < N && row >= 0 && col < M && col >= 0; }
	
	SPoint bruiter(int range, int N, int M);

};
std::ostream& operator<<(std::ostream& o, const SPoint& p);

inline bool inclus(SPoint tl, SPoint br, SPoint dim){
	return tl <= SPoint(0, 0) && br >= dim;
}