#include "PriceEntry.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

PriceEntry::PriceEntry(time_t rawtime, std::vector<double>& prices): date(rawtime), prices(prices) {}

void PriceEntry::convertToByteArr(std::vector<uint8_t>& bytearr) {

    size_t prices_size = prices.size();
    const uint8_t* prices_size_bytes = reinterpret_cast<const uint8_t*>(&prices_size);
    bytearr.insert(bytearr.end(), prices_size_bytes, prices_size_bytes + sizeof(size_t));

    const uint8_t* close_bytes = reinterpret_cast<const uint8_t*>(&date);
    bytearr.insert(bytearr.end(), close_bytes, close_bytes + sizeof(date));

    for (const auto& price : prices) {
        const uint8_t* price_bytes = reinterpret_cast<const uint8_t*>(&price);
        bytearr.insert(bytearr.end(), price_bytes, price_bytes + sizeof(price));
    }

}

void PriceEntry::convertToType(std::vector<uint8_t>& bytearr) {

    if (bytearr.size() < sizeof(size_t) + sizeof(time_t)) {
        throw std::invalid_argument("Byte array is too small for a PriceEntry object.");
    }

    size_t prices_size;
    std::memcpy(&prices_size, bytearr.data(), sizeof(size_t));

    if (bytearr.size() < sizeof(size_t) + sizeof(time_t) + prices_size * sizeof(double)) {
        throw std::invalid_argument("Byte array is incomplete.");
    }

    std::memcpy(&date, bytearr.data() + sizeof(size_t), sizeof(time_t));

    prices.clear();
    prices.reserve(prices_size); // Pre-allocate memory for efficiency
    size_t current_offset = sizeof(size_t) + sizeof(time_t);
    for (size_t i = 0; i < prices_size; ++i) {
        double price;
        std::memcpy(&price, bytearr.data() + current_offset, sizeof(double));
        prices.push_back(price);
        current_offset += sizeof(double);
    }
}

std::ostream& operator<<(std::ostream& os, const PriceEntry& entry) {
    os << entry.date << std::endl;
    for (auto it = entry.prices.begin(); it != entry.prices.end(); ++it) {
        os << *it << " ";
    }
    return os;
}
