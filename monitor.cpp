#include "monitor.h"

void CPU::initCPU() {
    std::ifstream file("/proc/cpuinfo");
    std::string line;

    //Get CPU Name
    while(std::getline(file, line)) {
        if(line.rfind("model name", 0) == 0) {
            auto pos = line.find(':');
            if(pos != std::string::npos) {
                CPUName = line.substr(pos + 2);
            }
            else {
                CPUName = "Unknown CPU";
            }
        }
    }

    //Get logical core count
    LogicalCoreCount = std::thread::hardware_concurrency();

    //Get physical core count

}

void CPU::UpdateCPU() {

}
