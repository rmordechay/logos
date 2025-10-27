#include "Lgs_Arena.h"
#include <cstdlib>

void* Lgd_Arena::allocate(const std::size_t size, const std::size_t align) {
    auto offset = currentOffset + (align - 1) & ~(align - 1);
    if (!currentBlock || offset + size > BLOCK_SIZE) {
        currentBlock = std::malloc(BLOCK_SIZE);
        blocks.push_back(currentBlock);
        offset = 0;
    }
    void* ptr = static_cast<char*>(currentBlock) + offset;
    currentOffset = offset + size;
    return ptr;
}

void Lgd_Arena::reset() {
    currentBlock = nullptr;
    currentOffset = 0;
    for (void* block : blocks) {
        std::free(block);
    }
    blocks.clear();
}

Lgd_Arena::~Lgd_Arena() {
    reset();
}
