#pragma once
#define BLOCK_SIZE 1024*1024
#include <vector>

#define ALIGN alignof(std::max_align_t)

struct Lgs_Alloc {
    void* ptr;
    size_t level;
};

class Lgs_Allocator {
public:
    size_t currentOffset = 0;
    void* currentBlock = nullptr;
    std::vector<void*> blocks;

    void* allocate(size_t size);
    void freeBlocks();
};
