#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <vector>
#include <chrono>
#include <thread>
#include <set>
#include <unistd.h>
#include <sstream>
#include <utility>

//CPU Object
class CPU {
public:
    //Static after initialization
    std::string CPUName;
    uint8_t PhysicalCoreCount = 0;
    uint8_t LogicalCoreCount = 0;

    //Needs to be updated
    uint8_t CPUTemperature = 0;
    uint8_t CPUUtilazation = 0;
    uint32_t CPUClockSpeed = 0;

    //Functions
    void initCPU();
    void UpdateCPU();
};

//GPU Object
class GPU {
public:
    //Static after initialization
    std::string GPUName;
    uint32_t ShaderCount = 0;
    uint32_t GPUVRAM = 0;

    //Needs to be updated
    uint8_t GPUTemperature = 0;
    uint8_t GPUUtilazation = 0;
    uint8_t GPUHotSpotTemperature = 0;
    uint8_t GPUMemoryTemperature = 0;
    uint32_t GPUClockSpeed = 0;
    uint32_t GPUUsedVRAM = 0;

    //Functions
    void initGPU();
    void UpdateGPU();
};

//Memory Object
class Memory {
    //Static after initialization
    std::string MemoryName;
    uint32_t TotalMemory = 0;

    //Needs to be updated
    uint8_t MemoryTemperature = 0;
    uint32_t UsedMemory = 0;
    uint32_t AvaiableMemory = 0;
    uint32_t FreeMemory = 0;
    uint32_t Buffer = 0;
    uint32_t SharedMemory = 0;

    //Functions
    void initMemory();
    void UpdateMemory();
};

//Storage Object
class Storage {
    //Static after initialization
    std::string DriveName;
    uint32_t StorageCapacity = 0;

    //Needs to be updated
    uint32_t UsedStorage = 0;
    uint32_t AvaiableStorage = 0;

    //Functions
    void initStorage();
    void UpdateStorage();
};
/*
//Process Object
class Process {
    //Static after initialization
    std::string ProcessName;
    float CPURessource = 0;
    float MemoryRessource = 0
    float NetworkUpload = 0;
    float NetworkDownload = 0;
    float StorageRead = 0;
    float StorageWrite = 0;

    //Functions
    void initProcess();
    void UpdateProcess();
}*/
