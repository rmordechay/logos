#include "logos/LgsAppCache.h"
#include "files/LgsFileMetadata.h"
#include "utils/LgsUtils.h"

void LgsAppCache::load(const fs::path& cacheFilePath) {
    if (!fs::exists(cacheFilePath)) return;
    std::ifstream inFile(cacheFilePath, std::ios::binary);
    if (!inFile) return;
    size_t count;
    inFile.read(reinterpret_cast<char*>(&count), sizeof(count));
    files.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        FileID id;
        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        size_t hash;
        inFile.read(reinterpret_cast<char*>(&hash), sizeof(hash));
        LgsFileType type;
        inFile.read(reinterpret_cast<char*>(&type), sizeof(type));
        size_t pathLength;
        inFile.read(reinterpret_cast<char*>(&pathLength), sizeof(pathLength));
        std::string pathStr(pathLength, '\0');
        inFile.read(&pathStr[0], pathLength);
        const fs::path filePath(pathStr);
        std::time_t lastWriteTime;
        inFile.read(reinterpret_cast<char*>(&lastWriteTime), sizeof(lastWriteTime));
        LgsFileMetadata fileMetadata(id, filePath, lastWriteTime, type);
        fileMetadata.hash = hash;
        files.push_back(fileMetadata);
    }
}

void LgsAppCache::save(const fs::path& cacheFilePath) const {
    if (fs::exists(cacheFilePath)) fs::remove(cacheFilePath);
    std::ofstream outFile(cacheFilePath, std::ios::binary | std::ios::trunc);
    const auto count = files.size();
    outFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& file : files) {
        outFile.write(reinterpret_cast<const char*>(&file.id), sizeof(file.id));
        outFile.write(reinterpret_cast<const char*>(&file.hash), sizeof(file.hash));
        outFile.write(reinterpret_cast<const char*>(&file.type), sizeof(file.type));
        const auto pathStr = file.path.string();
        const auto pathLength = pathStr.size();
        outFile.write(reinterpret_cast<const char*>(&pathLength), sizeof(pathLength));
        outFile.write(pathStr.data(), pathLength);
        outFile.write(reinterpret_cast<const char*>(&file.lastWritten), sizeof(file.lastWritten));
    }
}

void LgsAppCache::print() const {
    for (size_t i = 0; i < files.size(); ++i) {
        logInfo("id          = " + std::to_string(files[i].id) + '\n');
        logInfo("type        = " + std::to_string(files[i].type) + '\n');
        logInfo("hash        = " + std::to_string(files[i].hash) + '\n');
        logInfo("lastWritten = " + std::to_string(files[i].lastWritten) + '\n');
        logInfo("filePath    = " + files[i].path.string() + '\n');
        logInfo("---\n");
    }
}

void LgsAppCache::addFileMetadata(const size_t fileID, const fs::path& filePath, const LgsFileType fileType) {
    files.emplace_back(LgsFileMetadata(fileID, filePath, getLastWritten(filePath), fileType));
}

LgsFileMetadata* LgsAppCache::getAppConfigFile() {
    for (auto& metadata : files) {
        if (metadata.type == LGS_APP_CONFIG_FILE) {
            return &metadata;
        }
    }
    return nullptr;
}

bool LgsAppCache::fileExists(const std::filesystem::directory_entry& entry) const {
    for (auto metadata : files) {
        if (metadata.path == entry) {
            return true;
        }
    }
    return false;
}

size_t LgsAppCache::getHashByPath(const fs::path& path) const {
    for (auto fileMetadata : files) {
        if (fileMetadata.path == path) return fileMetadata.hash;
    }
    return 0;
}
