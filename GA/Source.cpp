#include "GAConfig.h"
#include "GeneticAlgorithm.h"
#include "PriceDataConverter.h"
#include "MeanPortfolioReturnCalculator.h"
#include "StandardDeviationReturnCalculator.h"
#include <chrono>

#define POPULATIONSIZE 100
#define GENERATIONS 500
#define CHROMOSOMESIZE 20
#define MUTATIONRATE 0.3
#define CROSSOVERRATE 0.6
#define THRESHOLD 0.00005
#define ELITISMRATE 0.1

int main() {

	PriceDataConverter::convert();
	
	GeneticAlgorithmConfig config;

	config.populationSize = POPULATIONSIZE;
	config.generations = GENERATIONS;
	config.chromosomeSize = CHROMOSOMESIZE;
	config.mutationRate = MUTATIONRATE;
	config.crossoverRate = CROSSOVERRATE;
	config.elitism = static_cast<int>(ELITISMRATE * POPULATIONSIZE);
	config.threshold = THRESHOLD;
	config.mutationType = new SwapMutation();
	config.selectionType = new HeuristicSelecton();
	
	std::vector<double> best;
	std::vector<double> average;

	auto start = std::chrono::high_resolution_clock::now();
	GeneticAlgorithm::getInstance(config).run(best, average);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time taken: " << duration.count() << " miliseconds" << std::endl;
}
