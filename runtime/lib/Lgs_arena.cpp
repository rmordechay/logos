class Arena {
    std::vector<void*> blocks;
    std::size_t blockSize;
    void* currentBlock;
    std::size_t currentOffset;

public:
    explicit Arena(const std::size_t blockSize = 4096) : blockSize(blockSize), currentBlock(nullptr), currentOffset(0) {}

    void* allocate(const std::size_t size, const std::size_t align = alignof(std::max_align_t)) {
        auto offset = currentOffset + (align - 1) & ~(align - 1); // align
        if (!currentBlock || offset + size > blockSize) {
            // allocate a new block
            currentBlock = std::malloc(blockSize);
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
        for (void* block : blocks)
            std::free(block);
        blocks.clear();
    }

    ~Arena() {
        for (void* block : blocks)
            std::free(block);
    }
};