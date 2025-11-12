#pragma once
#include "LgsFile.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

class LgsObjectFile final : public LgsFile {
public:
    LgsObject *obj = nullptr;

    explicit LgsObjectFile(const fs::path& path) : LgsFile(path) {}
    size_t hashFile() override;
    ~LgsObjectFile() override;
};

