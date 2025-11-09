#include "Lgs_Arena.h"
#include <cstdlib>

void* Lgs_Arena::allocate(const size_t size) {
    auto offset = currentOffset + (ALIGN - 1) & ~(ALIGN - 1);
    if (!currentBlock || offset + size > BLOCK_SIZE) {
        currentBlock = std::malloc(BLOCK_SIZE);
        blocks.push_back(currentBlock);
        offset = 0;
    }
    void* ptr = static_cast<char*>(currentBlock) + offset;
    currentOffset = offset + size;
    return ptr;
}

Lgs_Arena::~Lgs_Arena() {
    currentBlock = nullptr;
    currentOffset = 0;
    for (void* block : blocks) {
        std::free(block);
    }
    blocks.clear();
}
