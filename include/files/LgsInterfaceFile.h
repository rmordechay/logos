#pragma once
#include <files/LgsFile.h>

class LgsInterfaceFile final : public LgsFile {
public:
    LgsInterface* interface = nullptr;

    LgsInterfaceFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    ~LgsInterfaceFile() override;
};


