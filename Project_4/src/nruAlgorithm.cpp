#ifndef NRUALGORITHM_CPP
#define NRUALGORITHM_CPP

#include "nruAlgorithm.h"

NRUAlgorithm::~NRUAlgorithm()
{
    this->inputFile.close();
}

void NRUAlgorithm::pageReplacement(uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    uint32_t out = 0;
    if(this->inputCount < this->numberOfFrames)
    {
        out = this->inputCount;
        this->inputCount++;
    }
    else
    {
        out = this->getNRU();
        if(this->pageTable[this->frameTable[out]].dirty)
            totalWritesToDisk++;
        
        this->pageTable[this->frameTable[out]].dirty = 0;
        this->pageTable[this->frameTable[out]].referenced = 0;
        this->pageTable[this->frameTable[out]].valid = 0;
    }

    this->pageTable[tableIndex].pageFrameNumber = out;
    this->frameTable[out] = tableIndex;

    this->pageTable[tableIndex].dirty = 0;
    this->pageTable[tableIndex].referenced = 1;
    this->pageTable[tableIndex].valid = 1;

    if(this->refreshCount == this->refreshRate)
    {
        this->refreshCount = 0;
        this->resetRefresh();
    }

    this->refreshCount++;
    this->totalPageFaults++;
}

void NRUAlgorithm::printName()
{
    std::cout << "Algorithm: NRU" << std::endl; 
}

void NRUAlgorithm::resetRefresh()
{
    for(int i = 0; i < this->numberOfFrames; i++)
        this->pageTable[this->frameTable[i]].referenced = 0;
}

uint32_t NRUAlgorithm::getNRU()
{
    uint32_t deadMeat = 0;
    uint8_t value = 0;
    for(uint32_t i = 0; i < this->numberOfFrames; i++)
    {
        if(!this->pageTable[this->frameTable[i]].referenced && !this->pageTable[this->frameTable[i]].dirty)
            return i;
        uint8_t newValue = !this->pageTable[this->frameTable[i]].referenced << 1 + !this->pageTable[this->frameTable[i]].dirty;
        if(newValue > value)
        {
            value = newValue;
            deadMeat = i;
        }
    }
    return deadMeat;
}

#endif