#pragma once
namespace fs = std::filesystem;

using FileID = size_t;

struct LgsFileMetadata {
    FileID id = 0;
    fs::path filePath = "";
    fs::file_time_type lastWriteTime;

    LgsFileMetadata(const FileID id, const fs::path& filePath) : id(id), filePath(filePath) {}
    LgsFileMetadata(const FileID id, const fs::path& filePath, const fs::file_time_type& lastWriteTime) : id(id), filePath(filePath), lastWriteTime(lastWriteTime) {}
};

inline void saveMetadataVector(const std::vector<LgsFileMetadata>& files, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    const auto count = files.size();
    outFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& metadata : files) {
        outFile.write(reinterpret_cast<const char*>(&metadata.id), sizeof(metadata.id));
        const auto pathStr = metadata.filePath.string();
        const auto pathLength = pathStr.size();
        outFile.write(reinterpret_cast<const char*>(&pathLength), sizeof(pathLength));
        outFile.write(pathStr.data(), pathLength);
        const auto duration = metadata.lastWriteTime.time_since_epoch().count();
        outFile.write(reinterpret_cast<const char*>(&duration), sizeof(duration));
    }
    outFile.close();
}

inline std::vector<LgsFileMetadata> loadMetadataVector(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    size_t count;
    inFile.read(reinterpret_cast<char*>(&count), sizeof(count));
    std::vector<LgsFileMetadata> metadataList;
    metadataList.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        FileID id;
        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        size_t pathLength;
        inFile.read(reinterpret_cast<char*>(&pathLength), sizeof(pathLength));
        std::string pathStr(pathLength, '\0');
        inFile.read(&pathStr[0], pathLength);
        const fs::path filePath(pathStr);
        fs::file_time_type::rep duration;
        inFile.read(reinterpret_cast<char*>(&duration), sizeof(duration));
        const fs::file_time_type lastWriteTime{fs::file_time_type::duration(duration)};
        metadataList.push_back(LgsFileMetadata(id, filePath, lastWriteTime));
    }
    inFile.close();
    return metadataList;
}
