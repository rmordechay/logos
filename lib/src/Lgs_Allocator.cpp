#include "Lgs_Allocator.h"

#include <ostream>
#include <sys/mman.h>

void* Lgs_Allocator::allocate(const size_t size) {
    auto offset = currentOffset + (ALIGN - 1) & ~(ALIGN - 1);
    if (!currentBlock || offset + size > BLOCK_SIZE) {
        currentBlock = mmap(nullptr, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        // std::println("Allocated block: {}", currentBlock);
        blocks.push_back(currentBlock);
        offset = 0;
    }
    void* ptr = static_cast<char*>(currentBlock) + offset;
    currentOffset = offset + size;
    return ptr;
}

void Lgs_Allocator::freeBlocks() {
    for (const auto& block : blocks) {
        // std::println("Freeing block: {}", block);
        munmap(block, BLOCK_SIZE);
    }
    blocks.clear();
}