#pragma once
namespace fs = std::filesystem;

using FileID = size_t;

struct LgsFileMetadata {
    FileID id = 0;
    size_t hash = 0;
    fs::path filePath = "";
    fs::file_time_type lastWriteTime;

    LgsFileMetadata(const FileID id, const fs::path& filePath) : id(id), filePath(filePath) {}
    LgsFileMetadata(const FileID id, const fs::path& filePath, const fs::file_time_type& lastWriteTime) : id(id), filePath(filePath), lastWriteTime(lastWriteTime) {}
};

struct LgsAppMetadata {
    std::vector<LgsFileMetadata> files;

    LgsAppMetadata() = default;
    explicit LgsAppMetadata(std::vector<LgsFileMetadata> files) : files(std::move(files)) {}
};

inline void saveMetadata(const LgsAppMetadata& metadata, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    const auto count = metadata.files.size();
    outFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& file : metadata.files) {
        outFile.write(reinterpret_cast<const char*>(&file.id), sizeof(file.id));
        const auto pathStr = file.filePath.string();
        const auto pathLength = pathStr.size();
        outFile.write(reinterpret_cast<const char*>(&pathLength), sizeof(pathLength));
        outFile.write(pathStr.data(), pathLength);
        const auto duration = file.lastWriteTime.time_since_epoch().count();
        outFile.write(reinterpret_cast<const char*>(&duration), sizeof(duration));
    }
}

inline LgsAppMetadata loadMetadata(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) return LgsAppMetadata{};
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
    return LgsAppMetadata{std::move(metadataList)};
}