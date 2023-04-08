#ifndef VIRTUALMEMORYSIMULATION_H
#define VIRTUALMEMORYSIMULATION_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <memory>
#include <algorithm>
#include <cctype>
#include "common.h"

class VirtualMemorySimulation{
    private:
        void instructionFetch(const uint32_t memoryAddress);
        void loadWord(const uint32_t memoryAddress);
        void storeWord(const uint32_t memoryAddress);
        void modifyWord(const uint32_t memoryAddress);
        void printStatistics(void);

    protected:
        std::ifstream inputFile;
        uint8_t numberOfFrames;
        std::unique_ptr<entry_t[]> pageTable;
        uint32_t totalMemoryAccess, totalPageFaults, totalWritesToDisk, tableEntryTotal;
        uint16_t pageSize;
        virtual void pageReplacement(uint32_t memoryAddress){};
        virtual void printName(void){};
        event_t readMemoryTrace(uint32_t *memoryAddress);
        
    public:
        VirtualMemorySimulation(const uint8_t numberOfFrames, const std::string tracefile);
        void runSimulation(void);
        uint32_t getTotalMemoryAccess(void);
        uint32_t getTotalPageFaults(void);
        uint32_t getTotalWritesToDisk(void);
        uint32_t getNumberOfFrames(void);
};

#endif