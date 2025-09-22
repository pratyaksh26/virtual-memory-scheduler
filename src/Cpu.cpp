#include "Cpu.h"
#include <iostream>
#include <string>

Cpu::Cpu(MemoryManager& mem) : memory(mem), instructionCounter(0), toggle(false) {}

void Cpu::setInstructionCounter(int ic) {
    instructionCounter = ic;
}

int Cpu::execute(ProcessControlBlock& pcb) {
    while (true) {
        // Fetch
        std::string instruction = memory.read(instructionCounter);
        for(int i=0; i<4; ++i) instructionRegister[i] = instruction[i];
        instructionCounter++;
        pcb.timeCounter++;

        if (pcb.timeCounter > pcb.timeLimit) {
            return 2; // Time Limit Exceeded
        }

        // Decode and Execute
        if (instruction.substr(0, 2) == "GD") {
            MOS(pcb, 1); // GET DATA
        } else if (instruction.substr(0, 2) == "PD") {
            MOS(pcb, 2); // PUT DATA
        } else if (instruction.substr(0, 2) == "LR") {
            int addr = std::stoi(instruction.substr(2, 2));
            std::string data = memory.read(addr);
            for(int i=0; i<4; ++i) generalRegister[i] = data[i];
        } else if (instruction.substr(0, 2) == "SR") {
            int addr = std::stoi(instruction.substr(2, 2));
            memory.write(addr, std::string(generalRegister, 4));
        } else if (instruction.substr(0, 2) == "CR") {
            int addr = std::stoi(instruction.substr(2, 2));
            std::string mem_data = memory.read(addr);
            toggle = (std::string(generalRegister, 4) == mem_data);
        } else if (instruction.substr(0, 2) == "BT") {
            if (toggle) {
                int addr = std::stoi(instruction.substr(2, 2));
                setInstructionCounter(addr);
            }
        } else if (instruction.substr(0, 1) == "H") {
            MOS(pcb, 3); // HALT
            return 0; // Normal termination
        }
    }
}

void Cpu::MOS(ProcessControlBlock& pcb, int si) {
    if (si == 1) { // GD
        // For simplicity, we assume data is read from input and put directly into memory
        // A full implementation would handle this in the OS layer
    } else if (si == 2) { // PD
        if (pcb.lineCounter >= pcb.lineLimit) {
             // Line Limit Exceeded logic would be here, setting an error code
        } else {
            // Simplified: print to console
            int startAddr = std::stoi(std::string(instructionRegister).substr(2,2));
            for(int i=startAddr; i < startAddr + 10; ++i){
                std::cout << "Output: " << memory.read(i) << std::endl;
            }
            pcb.lineCounter++;
        }
    } else if (si == 3) { // H
        // Handled as termination in the main execution loop
    }
}