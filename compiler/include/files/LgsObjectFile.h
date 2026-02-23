#pragma once
#include <filesystem>

#include "LgsFile.h"
#include "types/LgsObject.h"
#include "codegen/LgsCodeGen.h"

class LgsObject;

class LgsObjectFile final : public LgsFile {
public:
    LgsObject* obj = nullptr;

    explicit LgsObjectFile(const fs::path& path) : LgsFile(path, CG_MODE_SRC) {}
    size_t hashFile() override;
    ~LgsObjectFile() override;
};

