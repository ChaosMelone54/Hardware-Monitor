#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <vector>
#include <chrono>
#include <thread>

//CPU Object
class CPU {
public:
    std::string CPUName;
    uint8_t PhysicalCoreCount = 0;
    uint8_t LogicalCoreCount = 0;
    uint8_t CPUTemperature = 0;
    uint8_t CPUUtilazation = 0;
    uint32_t CPUClockSpeed = 0;
}

//GPU Object
class GPU {
public:
    std::string GPUName;
    uint8_t GPUTemperature = 0;
    uint8_t GPUUtilazation = 0;
    uint8_t GPUHotSpotTemperature = 0;
    uint8_t GPUMemoryTemperature = 0;
    uint32_t GPUClockSpeed = 0;
    uint32_t ShaderCount = 0;
}

//Memory Object
class Memory {
    std::string DriveName;
    uint8_t MemoryTemperature = 0;
    uint32_t TotalMemory = 0;
    uint32_t UsedMemory = 0;
    uint32_t AvaiableMemory = 0;
    uint32_t FreeStorage = 0;
    uint32_t Buffer = 0;
    uint32_t SharedMemory = 0;
}

//Storage Object
class Storage {
    std::string DriveName;
    uint32_t StorageCapacity = 0;
    uint32_t UsedStorage = 0;
    uint32_t AvaiableStorage = 0;
}

//Process Object
class Process {
    std::string ProcessName;
    float CPURessource = 0;
    float MemoryRessource = 0
    float NetworkUpload = 0;
    float NetworkDownload = 0;
    float StorageRead = 0;
    float StorageWrite = 0;
}
