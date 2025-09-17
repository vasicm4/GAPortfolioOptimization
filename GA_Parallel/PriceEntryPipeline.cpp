#include "PriceEntryPipeline.h"
#include <fstream>
#include <iostream>

PriceEntryPipeline::PriceEntryPipeline(int size) : maxSize(size), entriesBuffer(std::list<PriceEntry*>()), currentFile(1) {}

PriceEntryPipeline& PriceEntryPipeline::getInstance(int size) {
	static PriceEntryPipeline instance(size);
	return instance;
}

bool PriceEntryPipeline::loadNextFile() {

    std::ifstream fin("./data/" + std::to_string(currentFile) + ".bin", std::ios::binary | std::ios::ate);
    if (!fin.is_open()) {
        return false;
    }

    std::streamsize fileSize = fin.tellg();
    fin.seekg(0, std::ios::beg);
    std::vector<uint8_t> fileBuffer(fileSize);
    fin.read(reinterpret_cast<char*>(fileBuffer.data()), fileSize);
    fin.close();

    PriceEntry* entry = nullptr;

    try {
        entry = new PriceEntry();
        entry->convertToType(fileBuffer);
        entriesBuffer.push_back(entry);
        if (entriesBuffer.size() > maxSize) {
            delete entriesBuffer.front();
            entriesBuffer.pop_front();
        }
    }
    catch (const std::invalid_argument const&) {
        delete entry;
        return false;
    }

    currentFile++;

    return !entriesBuffer.empty();
}

PriceEntry* PriceEntryPipeline::next() {
    if (entriesBuffer.empty()) {
        for (int i = 0; i < maxSize; i++) {
            if (!loadNextFile()) {
                break;
            }
        }
        if (entriesBuffer.empty()) {
            return nullptr;
        }
    }

    PriceEntry* result = entriesBuffer.front();
    entriesBuffer.pop_front();

    loadNextFile();

    return result;
}

void PriceEntryPipeline::reset() {
	for (PriceEntry* entry : entriesBuffer) {
		delete entry;
	}
	entriesBuffer.clear();
	currentFile = 0;
}