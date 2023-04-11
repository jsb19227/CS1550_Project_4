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

//Class that runs all the common functions of the program
class VirtualMemorySimulation{
    private:
        //Basic helper functions for the different memory accesses
        void instructionFetch(const uint32_t memoryAddress);
        void loadWord(const uint32_t memoryAddress);
        void storeWord(const uint32_t memoryAddress);
        void modifyWord(const uint32_t memoryAddress);

        //Prints stats at end of run
        void printStatistics(void);

    protected:
        //Input file
        std::ifstream inputFile;
        //# of frames
        uint8_t numberOfFrames;
        //Array of page table entries
        std::unique_ptr<entry_t[]> pageTable;
        //Stats
        uint32_t totalMemoryAccess, totalPageFaults, totalWritesToDisk, tableEntryTotal;
        //Page size
        uint16_t pageSize;
        //Functions that will be overloaded by algorithms
        virtual void pageReplacement(uint32_t memoryAddress){};
        virtual void printName(void){};
        //Reads line from file and decodes it
        event_t readMemoryTrace(uint32_t *memoryAddress);
        
    public:
        //Constructor
        VirtualMemorySimulation(const uint8_t numberOfFrames, const std::string tracefile);
        //Runs the simulation to completion
        void runSimulation(void);
        //Getters for the stats
        uint32_t getTotalMemoryAccess(void);
        uint32_t getTotalPageFaults(void);
        uint32_t getTotalWritesToDisk(void);
        uint32_t getNumberOfFrames(void);
};

#endif