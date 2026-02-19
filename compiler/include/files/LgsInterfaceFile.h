#pragma once
#include "types/LgsInterface.h"
#include "LgsUtils.h"
#include <files/LgsFile.h>

class LgsInterfaceFile final : public LgsFile {
public:
    LgsInterface* interface = nullptr;

    explicit LgsInterfaceFile(const fs::path& path) : LgsFile(path, CG_MODE_SRC) {}
    size_t hashFile() override;
    ~LgsInterfaceFile() override;
};

