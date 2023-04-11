#ifndef FIFOALGORITHM_H
#define FIFOALGORITHM_H

#include "virtualMemorySimulation.h"
#include <queue>

class FIFOAlgorithm : public VirtualMemorySimulation{
    private:
        //Queue for page table entries
        std::queue<uint32_t> pageQueue;

        //Overloads of parent functions
        virtual void pageReplacement(uint32_t memoryAddress);
        virtual void printName(void);
    public:
        //Constructor
        FIFOAlgorithm(const uint8_t numberOfFrames, const std::string traceFile) : VirtualMemorySimulation(numberOfFrames, traceFile){}
        //Destructor
        ~FIFOAlgorithm();
};

#endif