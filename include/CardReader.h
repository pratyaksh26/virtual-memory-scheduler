#pragma once

#include <fstream>
#include <string>
#include "MemoryManager.h"

// Handles reading the input file ("cards").
class CardReader {
public:
    CardReader(const std::string& filename);
    bool loadNextJob(MemoryManager& memory, int& startAddress);

private:
    std::ifstream file;
};