#pragma once
#include <vector>
#include "Lgs_Types.h"

#define BLOCK_SIZE 1024*1024
#define ALIGN alignof(std::max_align_t)

struct Lgs_Alloc {
    int64_t level;
    int64_t block;
};

class Lgs_Allocator {
public:
    size_t level = 0;
    size_t currentOffset = 0;
    void* currentBlock = nullptr;
    std::vector<void*> blocks;

    void* allocate(size_t size);
    void freeBlocks();
};
