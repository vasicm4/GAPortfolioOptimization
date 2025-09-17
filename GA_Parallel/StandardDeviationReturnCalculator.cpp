#include "StandardDeviationReturnCalculator.h"
#include "PriceEntryPipeline.h"
#include "MeanPortfolioReturnCalculator.h";
#include "PriceEntry.h"
#include <cmath>
#include <iostream>

StandardDeviationReturnCalculator::StandardDeviationReturnCalculator(std::vector<double>& returns, int size): deviations(std::vector<double>(size)) {
	calculateStandardDeviations(returns);
}

double StandardDeviationReturnCalculator::calculate(std::vector<double>& portfolio) {

	double deviation = 0;

	for (int i = 0; i < deviations.size(); i++) {
		deviation += pow(deviations[i] * portfolio[i], 2.0);
	}

	return deviation;
}

void StandardDeviationReturnCalculator::calculateStandardDeviations(std::vector<double>& returns) {

	PriceEntryPipeline& pipeline = PriceEntryPipeline::getInstance(20);

	std::vector<double> mean;

	PriceEntry* prev = pipeline.next();
	PriceEntry* curr = pipeline.next();

	double count = 0;

	while (curr != nullptr) {
		for (int i = 0; i < returns.size(); i++) {
			deviations[i] += pow(((curr->prices[i] / prev->prices[i]) - 1.0) - returns[i], 2.0);
		}
		count++;
		prev = curr;
		curr = pipeline.next();
	}

	for (int i = 0; i < returns.size(); i++) {
		deviations[i] /= count;
	}

	for (int i = 0; i < returns.size(); i++) {
		deviations[i] = sqrt(deviations[i]);
	}
	pipeline.reset();
}
