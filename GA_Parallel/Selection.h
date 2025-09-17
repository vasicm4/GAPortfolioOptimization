#pragma once
#include "Chromosome.h"
#include <vector>

class Selection {
protected:
	Selection() = default;
	~Selection() = default;
public:
	virtual void select(std::vector<Chromosome*>& parents, std::vector<double>& evaluate, std::vector<std::pair<Chromosome*, Chromosome*>>& pairs, double& sum) = 0;
};

class HeuristicSelecton : public Selection {
public:
	HeuristicSelecton() = default;
	~HeuristicSelecton() = default;
	void select(std::vector<Chromosome*>& parents, std::vector<double>& evaluate, std::vector<std::pair<Chromosome*, Chromosome*>>& pairs, double& sum) override;
};


