#ifndef NRUALGORITHM_CPP
#define NRUALGORITHM_CPP

#include "nruAlgorithm.h"

NRUAlgorithm::~NRUAlgorithm()
{
    //Closes input file
    this->inputFile.close();
}

void NRUAlgorithm::pageReplacement(uint32_t memoryAddress)
{
    //Get table index
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    //Mark new location
    uint32_t out = 0;
    if(this->inputCount < this->numberOfFrames)
    {
        //Fill the page table
        out = this->inputCount;
        this->inputCount++;
    }
    else
    {
        //Get not recently used and kick it out
        out = this->getNRU();
        if(this->pageTable[this->frameTable[out]].dirty)
            totalWritesToDisk++;
        
        this->pageTable[this->frameTable[out]].dirty = 0;
        this->pageTable[this->frameTable[out]].referenced = 0;
        this->pageTable[this->frameTable[out]].valid = 0;
    }

    //Put the new table entry into the page table
    this->pageTable[tableIndex].pageFrameNumber = out;
    this->frameTable[out] = tableIndex;

    this->pageTable[tableIndex].dirty = 0;
    this->pageTable[tableIndex].referenced = 1;
    this->pageTable[tableIndex].valid = 1;

    //If refresh rate is hit, set all references to 0
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
    //Prints algo name
    std::cout << "Algorithm: NRU" << std::endl; 
}

void NRUAlgorithm::resetRefresh()
{
    //Sets all references to 0
    for(int i = 0; i < this->numberOfFrames; i++)
        this->pageTable[this->frameTable[i]].referenced = 0;
}

uint32_t NRUAlgorithm::getNRU()
{
    //Gets the NRU value, if deadMeat was 0, had a tendency to eject earlier entries rather than even ejections
    //Incrementing new start ensures that ejections are spread out across the entire table and not just entries towards the front
    uint32_t deadMeat = this->newStart;
    uint8_t value = !this->pageTable[this->frameTable[deadMeat]].referenced << 1 + !this->pageTable[this->frameTable[deadMeat]].dirty;
    if(value == 3)
        return deadMeat;
    for(uint32_t i = 0; i < this->numberOfFrames; i++)
    {
        if(!this->pageTable[this->frameTable[i]].referenced && !this->pageTable[this->frameTable[i]].dirty)
            return i;
        //Create a value thats value is weighted based on the table provided to us
        uint8_t newValue = !this->pageTable[this->frameTable[i]].referenced << 1 + !this->pageTable[this->frameTable[i]].dirty;
        if(newValue > value)
        {
            value = newValue;
            deadMeat = i;
        }
    }
    //Increment and loop new start
    this->newStart++;
    if(this->newStart >= this->numberOfFrames)
        this->newStart = 0;
    return deadMeat;
}

#endif