#ifndef OPTALGORITHM_H
#define OPTALGORITHM_H

#include "virtualMemorySimulation.h"
#include <vector>

class OPTAlgorithm : public VirtualMemorySimulation{
    private:
        uint32_t inputCount; 
        std::unique_ptr<std::vector<uint32_t>[]> futureSight;
        std::unique_ptr<uint32_t[]> frameTable; 
        virtual void pageReplacement(uint32_t memoryAddress);
        virtual void printName(void);
        void instructionFetch(const uint32_t memoryAddress);
        void loadWord(const uint32_t memoryAddress);
        void storeWord(const uint32_t memoryAddress);
        void modifyWord(const uint32_t memoryAddress);
        uint32_t getOpt(void);
        void printStatistics(void);
    public:
        OPTAlgorithm(const uint8_t numberOfFrames, const std::string traceFile);
        ~OPTAlgorithm();
        void runSimulation(void);
};

#endif