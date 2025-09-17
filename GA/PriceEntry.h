#pragma once
#include<string>
#include<vector>
#include<ctime>
#include <iostream>

struct PriceEntry {
public:
	time_t date;
	std::vector<double> prices;
	PriceEntry(time_t rawtime, std::vector<double>& prices);
	~PriceEntry() = default;
	PriceEntry() = default;
	void convertToByteArr(std::vector<uint8_t>& bytearr);
	void convertToType(std::vector<uint8_t>& bytearr);
	friend std::ostream& operator<<(std::ostream& os, const PriceEntry& entry);
};


