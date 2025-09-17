#include "Mutation.h"
#include <random>

void SwapMutation::mutate(std::vector<Chromosome*>& children, double& rate) {

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<double> dist(0.0, 1.0);

	double randval = 0;

	//parallel for
	for (int i = 0; i < children.size(); i++) {
		randval = dist(gen);
		if (randval <= rate) {
			children[i]->mutate();
		}
	}

}
