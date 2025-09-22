#pragma once

#include <string>
#include "MemoryManager.h"
#include "ProcessControlBlock.h"

// Represents the CPU, handling instruction execution and registers.
class Cpu {
public:
    Cpu(MemoryManager& mem);
    
    // Executes user program instructions. Returns an interrupt code.
    int execute(ProcessControlBlock& pcb);

private:
    // Registers
    char instructionRegister[4];
    char generalRegister[4];
    int instructionCounter;
    bool toggle;

    // System Components
    MemoryManager& memory;

    // Helper functions
    void setInstructionCounter(int ic);
    void MOS(ProcessControlBlock& pcb, int si);
};