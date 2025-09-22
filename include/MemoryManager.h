#pragma once

#include <vector>
#include <string>
#include <optional>

const int TOTAL_MEMORY_WORDS = 300;
const int FRAME_SIZE = 10;

class MemoryManager {
public:
    MemoryManager();

    std::optional<int> allocateFrame();
    void freeFrame(int startFrame);
    
    std::string read(int address) const;
    void write(int address, const std::string& data);
    void printMemory() const;

private:
    std::vector<char> memory;
    std::vector<bool> frameInUse;
};