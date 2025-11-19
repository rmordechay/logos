#pragma once
#define BLOCK_SIZE 1024*4
#include <vector>

#define ALIGN alignof(std::max_align_t)

class Lgs_Allocator {
public:
    size_t currentOffset = 0;
    void* currentBlock = nullptr;
    std::vector<void*> blocks;

    void* allocate(size_t size);
    void print() const;
    ~Lgs_Allocator();
};
