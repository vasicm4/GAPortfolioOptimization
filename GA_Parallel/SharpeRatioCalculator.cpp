#include "SharpeRatioCalculator.h"
#include "StandardDeviationReturnCalculator.h"
#include "MeanPortfolioReturnCalculator.h"

SharpeRatioCalculator::SharpeRatioCalculator(MeanPortfolioReturnCalculator& meanCalculator, StandardDeviationReturnCalculator& deviationCalculator): deviationCalculator(deviationCalculator), returnCalculator(meanCalculator){
}

double SharpeRatioCalculator::calculate(std::vector<double>& portfolio) {
	return returnCalculator.calculate(portfolio) / deviationCalculator.calculate(portfolio);
}