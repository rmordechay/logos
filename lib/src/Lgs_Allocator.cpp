#include "Lgs_Allocator.h"

#include <cassert>
#include <ostream>
#include <sys/mman.h>

static constexpr auto align = alignof(std::max_align_t) - 1;

void* Lgs_Allocator::allocate(const size_t size, bool withLevel) {
    assert(level > 0);
    auto offset = currentOffset + align & ~align;
    if (!currentBlock || offset + size > BLOCK_SIZE) {
        const auto blockSize = std::max(BLOCK_SIZE, size);
        currentBlock = mmap(nullptr, blockSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        blocks.push_back(currentBlock);
        offset = 0;
        // std::println("Allocated block: {}", currentBlock);
    }
    void* ptr = static_cast<char*>(currentBlock) + offset;
    if (withLevel) static_cast<size_t*>(ptr)[0] = level;
    currentOffset = offset + size;
    //std::println("A ptr={} level={} block={}", ptr, level, blocks.size());
    return ptr;
}

void Lgs_Allocator::freeBlocks() {
    for (const auto& block : blocks) {
        // std::println("Freeing block: {}", block);
        munmap(block, BLOCK_SIZE);
    }
    blocks.clear();
}
