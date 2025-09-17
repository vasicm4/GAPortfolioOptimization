#include "Mutation.h"
#include <random>

#include <tbb/parallel_for.h>

void SwapMutation::mutate(std::vector<Chromosome*>& children, double& rate) {

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<double> dist(0.0, 1.0);

	double randval = 0;

	tbb::parallel_for(tbb::blocked_range<int>(0, static_cast<int>(children.size())), [&](tbb::blocked_range<int> r) {
		for (int i = r.begin(); i < r.end(); i++) {
			randval = dist(gen);
			if (randval <= rate) {
				children[i]->mutate();
			}
		}	
	});

}
