#ifndef FIFOALGORITHM_CPP
#define FIFOALGORITHM_CPP

#include "fifoAlgorithm.h"

FIFOAlgorithm::~FIFOAlgorithm()
{
    this->inputFile.close();
}

void FIFOAlgorithm::pageReplacement(uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    //Fills the page table
    if(this->pageQueue.size() < this->numberOfFrames)
        this->pageTable[tableIndex].pageFrameNumber =this->pageQueue.size();
    else
    {
        //Pops the front of the queue
        if(this->pageTable[this->pageQueue.front()].dirty)
            totalWritesToDisk++;
        
        this->pageTable[this->pageQueue.front()].dirty = 0;
        this->pageTable[this->pageQueue.front()].referenced = 0;
        this->pageTable[this->pageQueue.front()].valid = 0;

        this->pageTable[tableIndex].pageFrameNumber = this->pageTable[this->pageQueue.front()].pageFrameNumber;
        this->pageQueue.pop();
    }

    //Pushes new page to the queue
    this->pageQueue.push(tableIndex);
    this->pageTable[tableIndex].dirty = 0;
    this->pageTable[tableIndex].referenced = 1;
    this->pageTable[tableIndex].valid = 1;
    this->totalPageFaults++;
}

void FIFOAlgorithm::printName()
{
    //Prints algo name
    std::cout << "Algorithm: FIFO" << std::endl; 
}

#endif