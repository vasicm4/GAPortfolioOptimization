#pragma once

#include "SharpeRatioCalculator.h"
#include "GAConfig.h";
#include "Chromosome.h";
#include "Crossover.h"
#include <vector>;

class GeneticAlgorithm
{
private:	
	GeneticAlgorithmConfig config;
	std::vector<Chromosome*> population;
	GeneticAlgorithm(GeneticAlgorithmConfig config);
	~GeneticAlgorithm() = default;
	void initializePopulation();
	double evaluatePopulation(std::vector<Chromosome*>& population, std::vector<double>& evaluate, SharpeRatioCalculator& calculator);
	void elitism(std::vector<Chromosome*>& population, const std::vector<Chromosome*>& children);
public:
	GeneticAlgorithm(const GeneticAlgorithm&) = delete;
	GeneticAlgorithm& operator=(const GeneticAlgorithm&) = delete;
	static GeneticAlgorithm& getInstance(GeneticAlgorithmConfig config);
	void run(std::vector<double>& best, std::vector<double>& average);
};

