#pragma once
#include "Mutation.h"
#include "Selection.h"

struct GeneticAlgorithmConfig {
public:
    int populationSize;
    int generations;
    double mutationRate;
    double crossoverRate;
    int elitism;
    int chromosomeSize;
    double threshold;
    Mutation* mutationType;
    Selection* selectionType;
};