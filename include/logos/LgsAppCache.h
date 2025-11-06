#pragma once
#include "files/LgsFile.h"

struct LgsFileMetadata;

struct LgsAppCache {
    std::vector<LgsFileMetadata> files;
    std::vector<LgsFileMetadata> cached;
    std::vector<LgsFileMetadata> dirtyFiles;

    void load(const fs::path& cacheFilePath);
    void save(const fs::path& cacheFilePath) const;
    void print() const;
    size_t getHashByPath(const fs::path& path) const;
};
