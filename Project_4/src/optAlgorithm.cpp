#ifndef OPTALGORITHM_CPP
#define OPTALGORITHM_CPP

#include "optAlgorithm.h"

OPTAlgorithm::OPTAlgorithm(const uint8_t numberOfFrames, const std::string traceFile) : VirtualMemorySimulation(numberOfFrames, traceFile)
{
    //Constructor stuff
    this->inputCount = 0;
    futureSight = std::make_unique<std::vector<uint32_t>[]>(this->tableEntryTotal);
    frameTable = std::make_unique<uint32_t[]>(this->numberOfFrames);
    for(uint32_t i = 0; i < this->numberOfFrames; i++)
        frameTable[i] = 0;
    event_t newEvent = Ignore;
    uint32_t memAddress = 0, lineCount = 0;

    //Read in entire input file
    //The array is the number of pages
    //Each vector has when the next time that page will be accessed
    while(newEvent != Exit)
    {
        newEvent = this->readMemoryTrace(&memAddress);
        if(newEvent != Ignore && newEvent != Exit)
        {
            uint32_t tableIndex = static_cast<uint32_t>(memAddress / this->pageSize);
            futureSight[tableIndex].push_back(lineCount);
            lineCount++;
        }
    }

    //Close and reopen file
    this->inputFile.close();
    this->inputFile.open(traceFile);
}

OPTAlgorithm::~OPTAlgorithm()
{
    //Close file
    this->inputFile.close();
}

void OPTAlgorithm::pageReplacement(uint32_t memoryAddress)
{
    //Get table index
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    uint32_t out = 0;
    if(this->inputCount < this->numberOfFrames)
    {
        //Fill table
        out = this->inputCount;
        this->inputCount++;
    }
    else
    {
        //get optimal choice and eject it

        out = getOpt();
        if(this->pageTable[this->frameTable[out]].dirty)
            totalWritesToDisk++;
        
        this->pageTable[this->frameTable[out]].dirty = 0;
        this->pageTable[this->frameTable[out]].referenced = 0;
        this->pageTable[this->frameTable[out]].valid = 0;
    }

    //Put new page into the table

    this->pageTable[tableIndex].pageFrameNumber = out;
    this->frameTable[out] = tableIndex;

    this->pageTable[tableIndex].dirty = 0;
    this->pageTable[tableIndex].referenced = 1;
    this->pageTable[tableIndex].valid = 1;

    this->totalPageFaults++;
}

uint32_t OPTAlgorithm::getOpt()
{
    //Find the page that will be accessed farthest in the future
    uint32_t deadMeat = 0;
    uint32_t value = 0;
    for(uint32_t i = 0; i < this->numberOfFrames; i++)
    {
        if(this->futureSight[this->frameTable[i]].size() <= 0)
            return i;
        if(this->futureSight[this->frameTable[i]][0] > value)
        {
            value = this->futureSight[this->frameTable[i]][0];
            deadMeat = i;
        }
    }
    return deadMeat;
}

//Override the parent functions memory access functions
//Main difference is that the memory access also removes 
//The its memory access from future sight

void OPTAlgorithm::instructionFetch(const uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    if(!this->pageTable[tableIndex].valid)
        pageReplacement(memoryAddress);
    else
        this->pageTable[tableIndex].referenced = 1;
    this->totalMemoryAccess++;
    this->futureSight[tableIndex].erase(this->futureSight[tableIndex].begin());
}

void OPTAlgorithm::loadWord(const uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    if(!this->pageTable[tableIndex].valid)
        pageReplacement(memoryAddress);
    else
        this->pageTable[tableIndex].referenced = 1;
    this->totalMemoryAccess++;
    this->futureSight[tableIndex].erase(this->futureSight[tableIndex].begin());
}

void OPTAlgorithm::storeWord(const uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    if(!this->pageTable[tableIndex].valid)
        pageReplacement(memoryAddress);
    else
    {
        this->pageTable[tableIndex].referenced = 1;
        this->pageTable[tableIndex].dirty = 1;
    } 
    this->totalMemoryAccess++;
    this->futureSight[tableIndex].erase(this->futureSight[tableIndex].begin());
}

void OPTAlgorithm::modifyWord(const uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    if(!this->pageTable[tableIndex].valid)
        pageReplacement(memoryAddress);
    else
    {
        this->pageTable[tableIndex].referenced = 1;
        this->pageTable[tableIndex].dirty = 1;
    } 
    this->totalMemoryAccess += 2; 
    this->futureSight[tableIndex].erase(this->futureSight[tableIndex].begin());
}

//Override run simulation

void OPTAlgorithm::runSimulation()
{
    uint32_t memoryAddress;
    event_t memoryEvent = Ignore;
    while(memoryEvent != Exit)
    {
        switch (memoryEvent)
        {
            case Instruction:
                this->instructionFetch(memoryAddress);
                break;
            case Load:
                this->loadWord(memoryAddress);
                break;
            case Store:
                this->storeWord(memoryAddress);
                break;
            case Modify:
                this->modifyWord(memoryAddress);
                break;
            default:
                break;
        }
        memoryEvent = this->readMemoryTrace(&memoryAddress);
    }
    this->printName();
    this->printStatistics();
}

void OPTAlgorithm::printName()
{
    //Print algo name
    std::cout << "Algorithm: OPT" << std::endl; 
}

void OPTAlgorithm::printStatistics()
{
    //Print stats
    std::cout << "Number of frames: " << (int)this->numberOfFrames << std::endl;
    std::cout << "Total memory accesses: " << (int)this->totalMemoryAccess << std::endl;
    std::cout << "Total page faults: " << (int)this->totalPageFaults << std::endl;
    std::cout << "Total writes to disk: " << (int)this->totalWritesToDisk << std::endl;
}

#endif