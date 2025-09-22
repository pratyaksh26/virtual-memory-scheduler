#include "CardReader.h"
#include <iostream>

CardReader::CardReader(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open input file!");
    }
}

bool CardReader::loadNextJob(MemoryManager& memory, int& startAddress) {
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 4) == "$AMJ") {
            // Found a new job, now load the program code
            auto frame = memory.allocateFrame();
            if(!frame){
                std::cerr << "Error: No memory available for new job." << std::endl;
                return false;
            }
            startAddress = *frame;
            int currentAddress = startAddress;

            while (std::getline(file, line) && line.substr(0, 4) != "$DTA") {
                memory.write(currentAddress, line);
                currentAddress++;
            }
            // Assume $DTA is followed by $END
            return true;
        }
    }
    return false; // No more jobs
}