#include "SCell.h"

std::istream& operator>>(std::istream& in, SCell::EType& t) {
	char c;
	in >> c;
	t = static_cast<SCell::EType>(c);

	return in;
}