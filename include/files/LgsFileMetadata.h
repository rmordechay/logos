#pragma once
#include "data/LgsErrors.h"
#include "utils/LgsUtils.h"

using FileID = size_t;

enum LgsFileType {
    LGS_SRC_FILE,
    LGS_APP_CONFIG_FILE,
    LGS_ENV_FILE,
};

struct LgsFileMetadata {
    FileID id = 0;
    size_t hash = 0;
    fs::path path = "";
    LgsFileType type;
    std::time_t lastWritten;
    LgsFileMetadata(const FileID id, const fs::path& filePath, const std::time_t& lastWriteTime = 0, const LgsFileType type = LGS_SRC_FILE) : id(id), path(filePath), type(type), lastWritten(lastWriteTime) {}
};
