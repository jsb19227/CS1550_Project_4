#ifndef SECONDALGORITHM_H
#define SECONDALGORITHM_H

#include "virtualMemorySimulation.h"
#include <queue>

class SecondAlgorithm : public VirtualMemorySimulation{
    private:
        std::queue<uint32_t> pageQueue;
        virtual void pageReplacement(uint32_t memoryAddress);
        virtual void printName(void);
    public:
        SecondAlgorithm(const uint8_t numberOfFrames, const std::string traceFile) : VirtualMemorySimulation(numberOfFrames, traceFile){}
        ~SecondAlgorithm();
};

#endif