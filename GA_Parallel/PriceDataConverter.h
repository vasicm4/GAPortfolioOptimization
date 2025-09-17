#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

class PriceDataConverter
{
private:
	static time_t stringToRawtime(const std::string& datetime_str);
	static void convertToDoubles(const std::vector<std::string>& split, std::vector<double>& prices);
	static void stringSplit(std::string& str, std::vector<std::string>& tokens);
public:
	static void convert();
};

