#include "MeanPortfolioReturnCalculator.h"
#include "PriceEntryPipeline.h"
#include "PriceEntry.h"
#include <iostream>

#include <tbb/parallel_for.h>

MeanPortfolioReturnCalculator::MeanPortfolioReturnCalculator(int size): returns(std::vector<double>(size)) {
	calculateMeanReturns();
}


double MeanPortfolioReturnCalculator::calculate(std::vector<double>& portfolio) {

	double mean = 0;

	for (int i = 0; i < returns.size(); i++) {
		mean += returns[i] * portfolio[i];
	}

	return mean;
}

void MeanPortfolioReturnCalculator::calculateMeanReturns() {

	PriceEntryPipeline& pipeline = PriceEntryPipeline::getInstance(20);
	
	PriceEntry* prev = pipeline.next();
	PriceEntry* curr = pipeline.next();

	double count = 0;

	while (curr != nullptr) {

		for (int i = 0; i < returns.size(); i++) {
			returns[i] += (curr->prices[i] / prev->prices[i]) - 1.0;
		}

		count++;
		prev = curr;
		curr = pipeline.next();
	}

	for (int i = 0; i < returns.size(); i++) {
		returns[i] /= count;
	}

	pipeline.reset();
}
