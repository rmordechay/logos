#include "Lgs_Allocator.h"
#include <sys/mman.h>

void* Lgs_Allocator::allocate(const size_t size) {
    auto offset = currentOffset + (ALIGN - 1) & ~(ALIGN - 1);
    if (!currentBlock || offset + size > BLOCK_SIZE) {
        currentBlock = mmap(nullptr, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        blocks.push_back(currentBlock);
        offset = 0;
    }
    void* ptr = static_cast<char*>(currentBlock) + offset;
    currentOffset = offset + size;
    return ptr;
}

void deallocate(void* ptr, const size_t size) {
    std::memset(ptr, 0, size);
}

void Lgs_Allocator::free() {
    currentBlock = nullptr;
    currentOffset = 0;
    for (void* block : blocks) {
        munmap(block, BLOCK_SIZE);
    }
    blocks.clear();
}

void Lgs_Allocator::print() const {
    printf("Current offset:  %lu\n", currentOffset);
    printf("Current address: %p\n", currentBlock);
    printf("Blocks:\n");
    for (const auto block : blocks) {
        printf(" - block %p\n", block);
    }
    printf("\n");
}
