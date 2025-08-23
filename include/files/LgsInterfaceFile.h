#pragma once
#include <files/LgsFile.h>

class LgsInterfaceFile final : public LgsFile {
public:
    LgsInterface* interface = nullptr;

    LgsInterfaceFile(const size_t fileID, const std::string& name, const fs::path& path) : LgsFile(fileID, name, path) {}
    ~LgsInterfaceFile() override;
};


