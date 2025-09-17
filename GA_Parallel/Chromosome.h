#pragma once

#include "SharpeRatioCalculator.h"
#include <vector>

class Chromosome
{
private:
	Chromosome() = delete;
public:
	std::vector<double> values;
	Chromosome(int chromosomeSize);
	~Chromosome();
	Chromosome& operator=(const Chromosome& other);
	double evaluate(SharpeRatioCalculator& calculator);
	void mutate();
	void initialize();
};

