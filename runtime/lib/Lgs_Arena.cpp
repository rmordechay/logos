#define BLOCK_SIZE 1024*4
#include <vector>

class Lgd_Arena {
public:
    size_t currentOffset = 0;
    void* currentBlock = nullptr;
    std::vector<void*> blocks;

    void* allocate(const std::size_t size, const std::size_t align = alignof(std::max_align_t)) {
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

    void reset() {
        currentBlock = nullptr;
        currentOffset = 0;
        for (void* block : blocks) {
            std::free(block);
        }
        blocks.clear();
    }

    ~Lgd_Arena() {
        reset();
    }
};
