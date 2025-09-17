#pragma once
#include "PriceEntry.h"
#include <list>

class PriceEntryPipeline
{

private:

	std::list<PriceEntry*> entriesBuffer;
	int currentFile = 0;
	int maxSize = 0;
	PriceEntryPipeline(int size);
	~PriceEntryPipeline() = default;
	bool loadNextFile();

public:

	PriceEntryPipeline(const PriceEntryPipeline&) = delete;
	PriceEntryPipeline& operator=(const PriceEntryPipeline&) = delete;
	static PriceEntryPipeline& getInstance(int size);
	PriceEntry* next();
	void reset();
};

