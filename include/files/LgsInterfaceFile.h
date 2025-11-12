#pragma once
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"
#include <files/LgsFile.h>

class LgsInterfaceFile final : public LgsFile {
public:
    LgsInterface* interface = nullptr;

    LgsInterfaceFile(const fs::path& path) : LgsFile(path) {}
    size_t hashFile() override;
    ~LgsInterfaceFile() override;
};

