#ifndef OPTALGORITHM_H
#define OPTALGORITHM_H

#include "virtualMemorySimulation.h"
#include <vector>

class OPTAlgorithm : public VirtualMemorySimulation{
    private:
        //Counts number of page table entires
        uint32_t inputCount; 
        //Array of vectors that represent the memory locations next use
        std::unique_ptr<std::vector<uint32_t>[]> futureSight;
        //Frame table
        std::unique_ptr<uint32_t[]> frameTable; 

        //Overloads of the parent functions
        virtual void pageReplacement(uint32_t memoryAddress);
        virtual void printName(void);
        void instructionFetch(const uint32_t memoryAddress);
        void loadWord(const uint32_t memoryAddress);
        void storeWord(const uint32_t memoryAddress);
        void modifyWord(const uint32_t memoryAddress);

        //Gets the best choice for ejection
        uint32_t getOpt(void);
        void printStatistics(void);
    public:
        //Constructor
        OPTAlgorithm(const uint8_t numberOfFrames, const std::string traceFile);
        //Destructor
        ~OPTAlgorithm();
        //Override of parent runSimulation
        void runSimulation(void);
};

#endif