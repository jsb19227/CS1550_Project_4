#ifndef OPTALGORITHM_H
#define OPTALGORITHM_H

#include "virtualMemorySimulation.h"
#include <vector>

class OPTAlgorithm : public VirtualMemorySimulation{
    private:
        std::unique_ptr<std::vector<uint32_t>> futureSight;
        virtual void pageReplacement(uint32_t memoryAddress);
        virtual void printName(void);
    public:
        OPTAlgorithm(const uint8_t numberOfFrames, const std::string traceFile) : VirtualMemorySimulation(numberOfFrames, traceFile);
        ~NRUAlgorithm();
};

#endif