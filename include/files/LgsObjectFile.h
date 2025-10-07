#pragma once
#include "LgsFile.h"

class LgsObjectFile final : public LgsFile {
public:
    LgsObject *obj = nullptr;

    explicit LgsObjectFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    ~LgsObjectFile() override;
};


