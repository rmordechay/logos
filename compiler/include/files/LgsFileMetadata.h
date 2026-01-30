#pragma once

enum LgsFileType {
    LGS_SRC_FILE,
    LGS_APP_CONFIG_FILE,
    LGS_ENV_FILE,
};

struct LgsFileMetadata {
    size_t hash = 0;
    fs::path path = "";
    LgsFileType type;
    std::time_t lastWritten;
    explicit LgsFileMetadata(const fs::path& filePath, const std::time_t& lastWriteTime = 0, const LgsFileType type = LGS_SRC_FILE) : path(filePath), type(type), lastWritten(lastWriteTime) {}
};
