#include "OperatingSystem.h"
#include <iostream>
#include <string>
#include <vector>

OperatingSystem::OperatingSystem(const std::string& inputFile)
    : memoryManager(), cpu(memoryManager), cardReader(inputFile) {}

void OperatingSystem::run() {
    startExecution();
}

void OperatingSystem::startExecution() {
    int startAddress = 0;
    while (cardReader.loadNextJob(memoryManager, startAddress)) {
        // In this simple model, we execute one job completely before loading the next.
        // A true multiprogramming OS would use a job queue.
        ProcessControlBlock pcb(1, 100, 50); // Hardcoded Job ID, TTL, TLL
        
        cpu.setInstructionCounter(startAddress);
        int terminationCode = cpu.execute(pcb);
        terminate(pcb, terminationCode);
    }
}

void OperatingSystem::terminate(ProcessControlBlock& pcb, int code) {
    std::cout << "\nJob ID: " << pcb.jobId << " terminated. ";
    switch (code) {
        case 0: std::cout << "Normal Termination."; break;
        case 1: std::cout << "Error: Out of Data."; break;
        case 2: std::cout << "Error: Time Limit Exceeded."; break;
        case 3: std::cout << "Error: Operation Code Error."; break;
        case 4: std::cout << "Error: Operand Error."; break;
        case 5: std::cout << "Error: Invalid Page Fault."; break;
        case 6: std::cout << "Error: Line Limit Exceeded."; break;
    }
    std::cout << " Time Used: " << pcb.timeCounter << ", Lines Printed: " << pcb.lineCounter << std::endl;
    std::cout << "--------------------------------\n";
    // Here we would also free memory used by the process
}