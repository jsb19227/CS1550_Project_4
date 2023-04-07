#ifndef FIFOALGORITHM_CPP
#define FIFOALGORITHM_CPP

#include "fifoAlgorithm.h"

void FIFOAlgorithm::pageReplacement(uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    if(this->pageQueue.size() >= this->numberOfFrames)
    {
        if(this->pageTable[this->pageQueue.front()].dirty)
            totalWritesToDisk++;
        this->pageTable[this->pageQueue.front()].valid = 0;
        this->pageQueue.pop();
    }
    this->pageTable[tableIndex].pageFrameNumber = this->pageQueue.size() % this->totalMemoryAccess;
    this->pageQueue.push(tableIndex);
    this->pageTable[tableIndex].dirty = 0;
    this->pageTable[tableIndex].referenced = 0;
    this->pageTable[tableIndex].valid = 1;
}

void FIFOAlgorithm::printName()
{
    std::cout << "Algorithm: FIFO" << std::endl; 
}

#endif