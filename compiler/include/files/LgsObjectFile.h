#pragma once
#include "LgsFile.h"
#include "types/LgsObject.h"

class LgsObjectFile final : public LgsFile {
public:
    LgsObject* obj = nullptr;

    explicit LgsObjectFile(const fs::path& path) : LgsFile(path, CG_MODE_SRC) {}
    size_t hashFile() override;
    ~LgsObjectFile() override;
};

