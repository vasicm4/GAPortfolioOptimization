#include "PriceDataConverter.h"
#include "PriceEntry.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

void PriceDataConverter::stringSplit(std::string& str, std::vector<std::string>& tokens) {

	std::string token;
	std::istringstream tokenStream(str);

	while (getline(tokenStream, token, ',')) {
		tokens.push_back(token);
	}

}

std::time_t PriceDataConverter::stringToRawtime(const std::string& datetime_str) {

	std::tm timeinfo = {};
	std::istringstream ss(datetime_str);
	ss >> std::get_time(&timeinfo, "%Y-%m-%d %H:%M:%S");

	if (ss.fail()) {
		return static_cast<std::time_t>(-1);
	}

	return std::mktime(&timeinfo);

}

void PriceDataConverter::convertToDoubles(const std::vector<std::string>& split , std::vector<double>& prices) {

	for (int i = 1; i < split.size(); i++) {
		try {
			prices.push_back(std::stod(split[i]));
		}
		catch (const std::invalid_argument&) {
			std::cerr << "Error: Invalid argument for conversion: " << split[i] << std::endl;
		}
		catch (const std::out_of_range&) {
			std::cerr << "Error: Value out of range for conversion: " << split[i] << std::endl;
		}
	}
}

void PriceDataConverter::convert() {

	std::string data = "./data";

	if (!std::filesystem::exists(data)) {

		std::filesystem::create_directory(data);

		std::ifstream fin("data.csv");

		std::vector<std::string> split;

		int count = 0;

		if (fin.is_open()) {

			std::string line;

			std::getline(fin, line);

			while (std::getline(fin, line)) {
			
				std::vector<std::string> split;
				std::vector<double> prices;
				std::vector<uint8_t> byteArr;

				std::ofstream fout(data + '/' + std::to_string(count) + ".bin", std::ios::binary);

				stringSplit(line, split);
				convertToDoubles(split, prices);

				PriceEntry entry = PriceEntry(stringToRawtime(split[0]), prices);
				std::cout << entry << std::endl;
				entry.convertToByteArr(byteArr);

				std::cout << byteArr.size();

				fout.write(reinterpret_cast<const char*>(byteArr.data()), byteArr.size());

				fout.close();

				std::cout << "File " << count << " created successfully" << std::endl;

				count++;
			}
		}
		else {
			std::cerr << "There was an error with opening file" << std::endl;
		}
		
		fin.close();

	} 
}
