#pragma once

#include <vector>
#include "PriceEntryPipeline.h"

class StandardDeviationReturnCalculator
{
	std::vector<double> deviations;
public: 
	StandardDeviationReturnCalculator(std::vector<double>& returns, int size);
	void calculateStandardDeviations(std::vector<double>& returns);
	double calculate(std::vector<double>& portfolio);
};

