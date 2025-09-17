#pragma once
#include <vector>

class MeanPortfolioReturnCalculator
{
public:
	std::vector<double> returns;
	MeanPortfolioReturnCalculator(int size);
	void calculateMeanReturns();
	double calculate(std::vector<double>& portfolio);
};

