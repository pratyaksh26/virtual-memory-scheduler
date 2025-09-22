#include "MemoryManager.h"
#include <iostream>
#include <string>

MemoryManager::MemoryManager() {
    memory.resize(TOTAL_MEMORY_WORDS * 4, '$'); // 300 words * 4 chars/word
    frameInUse.resize(TOTAL_MEMORY_WORDS / FRAME_SIZE, false);
}

std::optional<int> MemoryManager::allocateFrame() {
    int frameNum = rand() % (TOTAL_MEMORY_WORDS / FRAME_SIZE);
    if (!frameInUse[frameNum]) {
        frameInUse[frameNum] = true;
        return frameNum * FRAME_SIZE;
    }
    return std::nullopt; // No free frame found (simplified)
}

void MemoryManager::freeFrame(int startFrame) {
    if (startFrame % FRAME_SIZE == 0) {
        frameInUse[startFrame / FRAME_SIZE] = false;
    }
}

std::string MemoryManager::read(int address) const {
    std::string content;
    for (int i = 0; i < 4; ++i) {
        content += memory[address * 4 + i];
    }
    return content;
}

void MemoryManager::write(int address, const std::string& data) {
    for (int i = 0; i < 4; ++i) {
        memory[address * 4 + i] = (i < data.length()) ? data[i] : '$';
    }
}

void MemoryManager::printMemory() const {
    for (int i = 0; i < TOTAL_MEMORY_WORDS; ++i) {
        std::cout << "M[" << i << "]: " << read(i) << std::endl;
    }
}