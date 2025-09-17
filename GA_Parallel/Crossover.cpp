#include "Crossover.h"
#include <random>

void Crossover::pair(std::vector<Chromosome*>& children, std::vector<std::pair<Chromosome*, Chromosome*>>& pairs) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(0.0, 1.0);

	double randval = 0;
	std::vector<double> diff(pairs[0].first->values.size());

	int j = 0;
	double sum = 0;

	for (int i = 0; i < children.size(); i += 2) {

		sum = 0;
		randval = dist(gen);

		for (int k = 0; k < pairs[0].first->values.size(); k++) {
			diff[k] = randval * (pairs[j].first->values[k] - pairs[j].second->values[k]);
		}

		for (int k = 0; k < pairs[0].first->values.size(); k++) {
			children[i]->values[k] = pairs[j].first->values[k] + diff[k];
			sum += children[i]->values[k];
		}

		for (int k = 0; k < pairs[0].first->values.size(); k++) {
			children[i]->values[k] = children[i]->values[k] / sum;
		}
		
		sum = 0;

		for (int k = 0; k < pairs[0].first->values.size(); k++) {
			children[i+1]->values[k] = pairs[j].second->values[k] + diff[k];
			sum += children[i+1]->values[k];
		}

		for (int k = 0; k < pairs[0].first->values.size(); k++) {
			children[i+1]->values[k] = children[i+1]->values[k] / sum;
		}

		j++;
	}
}
