#pragma once
#include <files/LgsFile.h>
#include <filesystem>

#include "types/LgsInterface.h"
#include "codegen/LgsCodeGen.h"

class LgsInterface;

class LgsInterfaceFile final : public LgsFile {
public:
    LgsInterface* interface = nullptr;

    explicit LgsInterfaceFile(const fs::path& path) : LgsFile(path, CG_MODE_SRC) {}
    size_t hashFile() override;
    ~LgsInterfaceFile() override;
};

