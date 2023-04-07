#ifndef FIFOALGORITHM_H
#define FIFOALGORITHM_H

#include "virtualMemorySimulation.h"
#include <queue>

class FIFOAlgorithm : public VirtualMemorySimulation{
    private:
        std::queue<uint32_t> pageQueue;
        virtual void pageReplacement(uint32_t memoryAddress) override;
        virtual void printName(void) override;
    public:
        FIFOAlgorithm(const uint8_t numberOfFrames, const std::string traceFile) : VirtualMemorySimulation(numberOfFrames, traceFile){}
        ~FIFOAlgorithm(){}
};

#endif