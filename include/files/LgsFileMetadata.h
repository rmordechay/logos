#pragma once
#include "data/LgsErrors.h"

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

    LgsFileMetadata(const FileID id, const fs::path& filePath, const LgsFileType type = LGS_SRC_FILE) : id(id), path(filePath), type(type) {
        const auto ftime = fs::last_write_time(path);
        const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
        );
        lastWritten = std::chrono::system_clock::to_time_t(sctp);
    }
    LgsFileMetadata(const FileID id, const fs::path& filePath, const std::time_t& lastWriteTime, const LgsFileType type = LGS_SRC_FILE) : id(id), path(filePath), type(type), lastWritten(lastWriteTime) {}
};
