#include "GeneticAlgorithm.h"
#include "SharpeRatioCalculator.h"
#include <limits>
#include <cmath>
#include <iostream>

#include <tbb/parallel_for.h>

GeneticAlgorithm::GeneticAlgorithm(GeneticAlgorithmConfig config): config(config), population(std::vector<Chromosome*>(config.populationSize)) {}

//parallel for
void GeneticAlgorithm::initializePopulation() {

	tbb::parallel_for(tbb::blocked_range<int>(0, config.populationSize), [&](tbb::blocked_range<int> r) {
		for (int i = r.begin(); i < r.end(); ++i) {
			population[i] = new Chromosome(config.chromosomeSize);
			population[i]->initialize();
		}
	});

}

double GeneticAlgorithm::evaluatePopulation(std::vector<Chromosome*>& population, std::vector<double>& evaluate, SharpeRatioCalculator& calculator) {
	
	double sum = 0;

	tbb::parallel_for(tbb::blocked_range<int>(0, config.populationSize), [&](tbb::blocked_range<int> r) {
		for (int i = r.begin(); i < r.end(); ++i) {
			evaluate[i] = population[i]->evaluate(calculator);
			sum += evaluate[i];
		}
	});

	double tmp;
	Chromosome* ptmp;

	for (int i = 0; i < config.populationSize; i++) {
		for (int j = i+1; j < config.populationSize; j++) {
			if (evaluate[i] > evaluate[j]) {
				tmp = evaluate[j];
				ptmp = population[j];
				evaluate[j] = evaluate[i];
				population[j] = population[i];
				evaluate[i] = tmp;
				population[i] = ptmp;
			}
			else {
				continue;
			}
		}
	}

	return sum;
}

void GeneticAlgorithm::elitism(std::vector<Chromosome*>& population, const std::vector<Chromosome*>& children) {
	int j = 0;

	for (int i = 0; i < config.elitism; i++) {
		population[i] = population[population.size() - i - 1];
		j++;
	}

	for (int i = config.elitism; i < config.populationSize; i++) {
		population[i] = children[children.size() - i - 1];
		j++;
	}

}

GeneticAlgorithm& GeneticAlgorithm::getInstance(GeneticAlgorithmConfig config) {
	static GeneticAlgorithm instance(config);
	return instance;
}

void GeneticAlgorithm::run(std::vector<double>& bestList, std::vector<double>& averageList) {
	
	std::cout << "GA Stared" << std::endl;

	initializePopulation();

	std::cout << "Population Initialized" << std::endl;
	
	int bestIterations = 0;
	double lastBest = 0;
	Chromosome* lastBestChromosome = nullptr;

	std::vector<Chromosome*> children(config.populationSize);

	for (int i = 0; i < config.populationSize; ++i) {
		children[i] = new Chromosome(config.chromosomeSize);
	}

	std::vector<std::pair<Chromosome*, Chromosome*>> pairs(config.populationSize/2);
	std::vector<double> evaluated(config.populationSize);

	double sum = 0;
	double average = 0;

	double best = 0;
	Chromosome* bestChromosome = nullptr;

	MeanPortfolioReturnCalculator meanCalculator(config.chromosomeSize);
	StandardDeviationReturnCalculator deviationCalculator(meanCalculator.returns, config.chromosomeSize);
	SharpeRatioCalculator calculator{ meanCalculator , deviationCalculator };

	for (int i = 1; i < config.generations; i++) {
		
		sum = 0;
		average = 0;
		best = 0;

		sum = evaluatePopulation(population, evaluated, calculator);
		average = sum / static_cast<double>(config.populationSize);
		bestChromosome = population[population.size() - 1];
		best = evaluated[evaluated.size() - 1];

		std::cout << average << " " << best << std::endl;

		config.selectionType->select(population, evaluated, pairs, sum);

		Crossover::pair(children, pairs);

		config.mutationType->mutate(children, config.mutationRate);

		evaluatePopulation(children, evaluated, calculator);

		elitism(population, children);

		bestList.push_back(best);
		averageList.push_back(average);

		std::cout << "Generation " << i << " Best: " << best << std::endl;

		if (abs(lastBest - best) < config.threshold) {
			for (auto it = bestChromosome->values.begin(); it != bestChromosome->values.end(); ++it) {
				std::cout << *it << std::endl;
			}
			return;
		}

		if (lastBest > best) {
			lastBest = best;
			lastBestChromosome = bestChromosome;
			bestIterations = 0;
		}
		else {
			bestIterations++;
		}
	}

	for (auto it = bestChromosome->values.begin(); it != bestChromosome->values.end(); ++it) {
		std::cout << *it << std::endl;
	}
}
