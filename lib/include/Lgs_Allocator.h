#pragma once
#include <vector>

constexpr size_t BLOCK_SIZE = 1024*1024;

class Lgs_Allocator {
public:
    size_t level{};
    size_t currentOffset{};
    void* currentBlock{};
    std::vector<void*> blocks;

    void* allocate(size_t size, bool withLevel = true);
    void freeBlocks();
};
