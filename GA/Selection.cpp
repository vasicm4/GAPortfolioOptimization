#include "Selection.h"
#include <random>

void HeuristicSelecton::select(std::vector<Chromosome*>& parents, std::vector<double>& evaluate, std::vector<std::pair<Chromosome*, Chromosome*>>& pairs, double& sum) {
    
    std::random_device rd;
    std::mt19937 g(rd());

    int num_parents = static_cast<int>(parents.size());
    int fittest_half_size = num_parents / 2;

    for (int i = 0; i < pairs.size(); i++) {
        int parent1_idx = std::uniform_int_distribution<>(fittest_half_size, num_parents-1)(g);
        pairs[i].first = parents[parent1_idx];

        int parent2_idx = std::uniform_int_distribution<>(fittest_half_size, num_parents-1)(g);
        pairs[i].second = parents[parent2_idx];
    }

}