#ifndef NRUALGORITHM_H
#define NRUALGORITHM_H

#include "virtualMemorySimulation.h"

class NRUAlgorithm : public VirtualMemorySimulation{
    private:
        uint32_t refreshRate, refreshCount, inputCount;
        std::unique_ptr<uint32_t[]> frameTable; 
        virtual void pageReplacement(uint32_t memoryAddress);
        virtual void printName(void);
        uint32_t getNRU(void);
        void resetRefresh(void);
    public:
        NRUAlgorithm(const uint8_t numberOfFrames, const std::string traceFile, const uint32_t refresh) : VirtualMemorySimulation(numberOfFrames, traceFile)
        {
            this->refreshRate = refresh; 
            this->refreshCount = 0; 
            this->inputCount = 0;
            this->frameTable = std::make_unique<uint32_t[]>(this->numberOfFrames);
            for(int i = 0; i < this->numberOfFrames; i++)
                this->frameTable[i] = 0;
        }
        ~NRUAlgorithm();
};

#endif