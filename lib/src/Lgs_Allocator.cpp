#include "Lgs_Allocator.h"
#include <sys/mman.h>

void* Lgs_Allocator::allocate(const size_t size) {
    auto offset = currentOffset + (ALIGN - 1) & ~(ALIGN - 1);
    if (!currentBlock || offset + size > BLOCK_SIZE) {
        currentBlock = mmap(nullptr, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        blocks.push_back(currentBlock);
        offset = 0;
        // std::println("Allocated block: {}", currentBlock);
    }
    void* ptr = static_cast<char*>(currentBlock) + offset;
    auto* header = static_cast<size_t*>(ptr);
    header[0] = level;
    currentOffset = offset + size;
    // std::println("A ptr={} level={} block={}", ptr, level, blocks.size());
    return ptr;
}

void Lgs_Allocator::freeBlocks() {
    for (const auto& block : blocks) {
        // std::println("Freeing block: {}", block);
        munmap(block, BLOCK_SIZE);
    }
    blocks.clear();
}
