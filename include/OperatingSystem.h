#pragma once

#include "MemoryManager.h"
#include "Cpu.h"
#include "CardReader.h"
#include <memory>

// The main coordinator for the entire OS simulation.
class OperatingSystem {
public:
    OperatingSystem(const std::string& inputFile);
    void run();

private:
    void startExecution();
    void terminate(ProcessControlBlock& pcb, int code);

    MemoryManager memoryManager;
    Cpu cpu;
    CardReader cardReader;
};