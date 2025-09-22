#include "OperatingSystem.h"
#include <iostream>

int main() {
    try {
        OperatingSystem os("input.txt");
        os.run();
    } catch (const std::exception& e) {
        std::cerr << "A fatal error occurred: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "\nOS Simulation finished." << std::endl;
    return 0;
}