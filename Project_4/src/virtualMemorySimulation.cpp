#ifndef VIRTUALMEMORYSIMULATION_CPP
#define VIRTUALMEMORYSIMULATION_CPP

#include "virtualMemorySimulation.h"

VirtualMemorySimulation::VirtualMemorySimulation(const uint8_t numberOfFrames, const std::string tracefile)
{
    this->numberOfFrames = numberOfFrames;
    
    this->inputFile.open(tracefile);
    if(!this->inputFile.is_open())
    {
        std::cerr << "Trace file couldn't be opened..." << std::endl;
        exit(1);
    }

    this->pageSize = (1 << 12) / this->numberOfFrames;
    this->tableEntryTotal = static_cast<long>(1 << 31) / this->pageSize;
    this-> pageTable = std::make_unique<entry_t[]>(this->tableEntryTotal);
    entry_t temp = {0, 0, 0, 0, 0};
    for(int i = 0; i < this->tableEntryTotal; i++)
        this->pageTable[i] = temp;

    this->totalMemoryAccess = 0;
    this->totalPageFaults = 0;
    this->totalWritesToDisk = 0;
    this->tableEntryTotal = 0;
}

VirtualMemorySimulation::~VirtualMemorySimulation()
{
    this->inputFile.close();
}

event_t VirtualMemorySimulation::readMemoryTrace(uint32_t *memoryAddress)
{
    if(this->inputFile.eof())
        return Exit;
    
    event_t returnVal;
    std::string line;
    std::getline(this->inputFile, line);

    if(line.length() <= 0)
        return Exit;
    
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
    if(line.at(0) == 'I')
        returnVal = Instruction;
    else if(line.at(0) == 'L')
        returnVal = Load;
    else if(line.at(0) == 'S')
        returnVal = Store;
    else if(line.at(0) == 'M')
        returnVal = Modify;
    else
        returnVal = Ignore;

    if(returnVal != Ignore)
        *memoryAddress = std::stoul(line.substr(1, 8), nullptr, 16);

    return returnVal;
}

void VirtualMemorySimulation::instructionFetch(const uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    if(!this->pageTable[tableIndex].valid)
        pageReplacement(memoryAddress);
}

void VirtualMemorySimulation::loadWord(const uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    if(!this->pageTable[tableIndex].valid)
        pageReplacement(memoryAddress);
    else
        this->pageTable[tableIndex].referenced = 1;
}

void VirtualMemorySimulation::storeWord(const uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    if(!this->pageTable[tableIndex].valid)
        pageReplacement(memoryAddress);
    else
    {
        this->pageTable[tableIndex].referenced = 1;
        this->pageTable[tableIndex].dirty = 1;
    } 
}

void VirtualMemorySimulation::modifyWord(const uint32_t memoryAddress)
{
    uint32_t tableIndex = static_cast<uint32_t>(memoryAddress / this->pageSize);
    if(!this->pageTable[tableIndex].valid)
        pageReplacement(memoryAddress);
    else
    {
        this->pageTable[tableIndex].referenced = 1;
        this->pageTable[tableIndex].dirty = 1;
    }  
}

void VirtualMemorySimulation::runSimulation()
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

void VirtualMemorySimulation::printStatistics()
{
    std::cout << "Number of frames: " << (int)this->numberOfFrames << std::endl;
    std::cout << "Total memory accesses: " << (int)this->totalMemoryAccess << std::endl;
    std::cout << "Total page faults: " << (int)this->totalPageFaults << std::endl;
    std::cout << "Total writes to disk: " << (int)this->totalWritesToDisk << std::endl;
}
#endif