#pragma once
#include "Chromosome.h"
#include <vector>

class Crossover
{
public:
	static void pair(std::vector<Chromosome*>& children, std::vector<std::pair<Chromosome*, Chromosome*>>& pairs);
};

