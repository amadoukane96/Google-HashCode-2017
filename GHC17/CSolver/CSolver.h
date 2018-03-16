#pragma once
#include "modeles/CInput.h"
#include "modeles/CSolution.h"

template<typename FAlgo>
class CSolver
{
private:
	CInput* in;
	FAlgo algo;
public:
	CSolver();
	CSolver(CInput* data, FAlgo a);

	CSolution solve();
};

template<typename FAlgo>
inline CSolver<FAlgo>::CSolver(): in(nullptr)
{
}

template<typename FAlgo>
inline CSolver<FAlgo>::CSolver(CInput* data, FAlgo a): in(data), algo(a)
{
}

template<typename FAlgo>
inline CSolution CSolver<FAlgo>::solve()
{
	CSolution sln = algo(in);
	//std::cout << "solved ! " << std::endl;
	return sln;
}
