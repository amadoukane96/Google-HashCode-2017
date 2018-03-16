#pragma once 
#include <set>
#include <vector>
#include "modeles/SPoint.h"
#include "modeles/SCell.h"
#include <list>
#include "modeles/CInput.h"


std::vector<SPoint> shortestPath(CInput* map, SPoint start, SPoint end, std::vector<SPoint> paths, SPoint ignore);
std::vector<SPoint> Takahashi_steiner_tree(CInput* map, std::vector<SPoint> terminals, unsigned int loops, SPoint ignore);

