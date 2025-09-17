#pragma once
#include <vector>
#include "StandardDeviationReturnCalculator.h"
#include "MeanPortfolioReturnCalculator.h"

class SharpeRatioCalculator
{
	StandardDeviationReturnCalculator deviationCalculator;
	MeanPortfolioReturnCalculator returnCalculator;
public: 
	SharpeRatioCalculator(MeanPortfolioReturnCalculator& meanCalculator, StandardDeviationReturnCalculator& deviationCalculator);
	double calculate(std::vector<double>& portfolio);
};

