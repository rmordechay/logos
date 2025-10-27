#pragma once
#define BLOCK_SIZE 1024*4
#include <vector>

class Lgd_Arena {
public:
    size_t currentOffset = 0;
    void* currentBlock = nullptr;
    std::vector<void*> blocks;

    void* allocate(std::size_t size, std::size_t align = alignof(std::max_align_t));
    void reset();
    ~Lgd_Arena();
};
