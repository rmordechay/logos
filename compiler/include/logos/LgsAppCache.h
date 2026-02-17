#pragma once
#include "files/LgsFile.h"

struct LgsFileMetadata;

enum LgsFileType {
    LGS_SRC_FILE,
    LGS_APP_CONFIG_FILE,
    LGS_ENV_FILE,
};

struct LgsFileMetadata {
    size_t hash = 0;
    const fs::path path;
    LgsFileType type;
    std::time_t lastWritten;
    explicit LgsFileMetadata(const fs::path& filePath, const std::time_t& lastWriteTime = 0, const LgsFileType type = LGS_SRC_FILE) : path(filePath), type(type), lastWritten(lastWriteTime) {}
};

struct LgsAppCache {
    fs::path cacheFile;
    std::vector<LgsFileMetadata> files;
    std::vector<LgsFileMetadata> dirtyFiles;

    void load(const fs::path& cacheFilePath);
    void save(const fs::path& cacheFilePath) const;
    void addFileMetadata(const fs::path& filePath, LgsFileType fileType);
    LgsFileMetadata* getAppConfigFile();
    size_t getHashByPath(const fs::path& path) const;
    bool fileExists(const fs::path& entry) const;
    void print() const;
};
