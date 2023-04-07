#ifndef SECONDALGORITHM_CPP
#define SECONDALGORITHM_CPP

#include "secondAlgorithm.h"

SecondAlgorithm::~SecondAlgorithm()
{
    this->inputFile.close();
}

void SecondAlgorithm::pageReplacement(uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    if(this->pageQueue.size() < this->numberOfFrames)
        this->pageTable[tableIndex].pageFrameNumber =this->pageQueue.size();
    else
    {
        while(this->pageTable[this->pageQueue.front()].referenced)
        {
            this->pageTable[this->pageQueue.front()].referenced = 0;
            this->pageQueue.push(this->pageQueue.front());
            this->pageQueue.pop();
        }
        if(this->pageTable[this->pageQueue.front()].dirty)
            totalWritesToDisk++;
        
        this->pageTable[this->pageQueue.front()].dirty = 0;
        this->pageTable[this->pageQueue.front()].referenced = 0;
        this->pageTable[this->pageQueue.front()].valid = 0;

        this->pageTable[tableIndex].pageFrameNumber = this->pageTable[this->pageQueue.front()].pageFrameNumber;
        this->pageQueue.pop();
    }

    this->pageQueue.push(tableIndex);
    this->pageTable[tableIndex].dirty = 0;
    this->pageTable[tableIndex].referenced = 1;
    this->pageTable[tableIndex].valid = 1;
    this->totalPageFaults++;
}

void SecondAlgorithm::printName()
{
    std::cout << "Algorithm: 2nd" << std::endl; 
}

#endif