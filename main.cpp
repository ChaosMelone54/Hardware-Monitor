#include "monitor.cpp"
#include "monitor.h"
#include <iostream>

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>

int main() {
    CPU cpu;

    cpu.initCPU();

    unsigned int logicalCpusCpp = std::thread::hardware_concurrency();

    std::cout << "CPU: " << cpu.CPUName << std::endl;
    std::cout << "Logical Cores: " << static_cast<unsigned int>(cpu.LogicalCoreCount) << std::endl;
    std::cout << "Physical Cores: " << static_cast<unsigned int>(cpu.PhysicalCoreCount) << std::endl;
}
