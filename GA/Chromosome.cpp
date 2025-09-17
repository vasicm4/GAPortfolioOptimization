#include "Chromosome.h"
#include "SharpeRatioCalculator.h"
#include <random>

Chromosome::Chromosome(int chromosomeSize): values(std::vector<double>(chromosomeSize)) {}

Chromosome::~Chromosome() {}

Chromosome& Chromosome::operator=(const Chromosome& other) {
	for (int i = 0; i < other.values.size(); i++) {
		values[i] = other.values[i];
	}
	return *this;
}

double Chromosome::evaluate(SharpeRatioCalculator& calculator) {
	return calculator.calculate(values);
}

void Chromosome::mutate() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> distInt(0, static_cast<int>(values.size()));
	static std::uniform_real_distribution<double> distDouble(0.0, 0.2);

	int	rand1 = distInt(gen) % values.size();
	int	rand2 = distInt(gen) % values.size();

	double change = distDouble(gen);

	values[rand1] += change;
	values[rand2] -= change;
}


void Chromosome::initialize() {

	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);

	double sum = 0.0;
	
	for (int i = 0; i < values.size(); i++) {
		values[i] = dist(gen);
		sum += values[i];
	}

	for (auto it = values.begin(); it != values.end(); ++it) {
		*it /= sum;
	}

}