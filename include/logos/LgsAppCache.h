#pragma once
#include "files/LgsFile.h"

struct LgsAppCache {
    fs::path cacheFilePath;
    std::vector<LgsFileMetadata> files;
    std::vector<LgsFileMetadata> cached;
    std::vector<LgsFileMetadata> dirtyFiles;

    void load();
    void save() const;
    void print() const;
    size_t getHashByPath(const fs::path& path) const;
};
