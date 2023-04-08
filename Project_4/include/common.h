#ifndef COMMON_H
#define COMMON_H

#include <cstdint>

enum AlgorithmChoice{
    opt,
    fifo,
    second,
    nru
};
typedef AlgorithmChoice algo_t;

enum MemoryEvent{
    Instruction,
    Load,
    Store,
    Modify,
    Ignore,
    Exit
};
typedef MemoryEvent event_t;

struct PageTableEntry{
    uint8_t protection;
    uint8_t dirty;
    uint8_t referenced;
    uint8_t valid;
    uint32_t pageFrameNumber;
};
typedef struct PageTableEntry entry_t;

#endif