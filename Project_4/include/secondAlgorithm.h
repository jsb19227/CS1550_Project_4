#ifndef SECONDALGORITHM_H
#define SECONDALGORITHM_H

#include "virtualMemorySimulation.h"
#include <queue>

class SecondAlgorithm : public VirtualMemorySimulation{
    private:
        //Queue for page table entries
        std::queue<uint32_t> pageQueue;
        
        //Overloads of parent functions
        virtual void pageReplacement(uint32_t memoryAddress);
        virtual void printName(void);
    public:
        //Constructor that calls the parent constructor
        SecondAlgorithm(const uint8_t numberOfFrames, const std::string traceFile) : VirtualMemorySimulation(numberOfFrames, traceFile){}
        //Destructor
        ~SecondAlgorithm();
};

#endif