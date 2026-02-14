#pragma once
#include "files/LgsFile.h"
#include "files/LgsFileMetadata.h"

struct LgsFileMetadata;

struct LgsAppCache {
    fs::path cacheFile;
    std::vector<LgsFileMetadata> files;
    std::vector<LgsFileMetadata> dirtyFiles;

    void load(const fs::path& cacheFilePath);
    void save(const fs::path& cacheFilePath) const;
    void print() const;
    void addFileMetadata(const fs::path& filePath, LgsFileType fileType);
    LgsFileMetadata* getAppConfigFile();
    bool fileExists(const fs::path& entry) const;
    size_t getHashByPath(const fs::path& path) const;
};
