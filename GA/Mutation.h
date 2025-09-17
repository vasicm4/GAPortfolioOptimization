#pragma once
#include "Chromosome.h"
#include <vector>

class Mutation {
protected:
	Mutation() = default;
	~Mutation() = default;
public:
	virtual void mutate(std::vector<Chromosome*>& children, double& rate) = 0;
};

class SwapMutation : public Mutation {
public:
	SwapMutation() = default;
	~SwapMutation() = default;
	void mutate(std::vector<Chromosome*>& children, double& rate) override;
};


