#ifndef NRUALGORITHM_H
#define NRUALGORITHM_H

#include "virtualMemorySimulation.h"

class NRUAlgorithm : public VirtualMemorySimulation{
    private:
        //Basic variables for algo
        uint32_t refreshRate, refreshCount, inputCount, newStart;
        //Frame table
        std::unique_ptr<uint32_t[]> frameTable; 

        //Overloads of parent functions
        virtual void pageReplacement(uint32_t memoryAddress);
        virtual void printName(void);

        //gets the nru for ejection
        uint32_t getNRU(void);
        //Sets all references to 0
        void resetRefresh(void);
    public:
        //Basic constructor
        NRUAlgorithm(const uint8_t numberOfFrames, const std::string traceFile, const uint32_t refresh) : VirtualMemorySimulation(numberOfFrames, traceFile)
        {
            this->refreshRate = refresh; 
            this->refreshCount = 0; 
            this->inputCount = 0;
            this->frameTable = std::make_unique<uint32_t[]>(this->numberOfFrames);
            for(int i = 0; i < this->numberOfFrames; i++)
                this->frameTable[i] = 0;
            this->newStart = 0;
        }
        //Destructor
        ~NRUAlgorithm();
};

#endif