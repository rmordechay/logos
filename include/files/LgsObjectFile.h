#pragma once
#include "LgsFile.h"

class LgsObjectFile final : public LgsFile {
public:
    LgsObject *obj = nullptr;

    explicit LgsObjectFile(const size_t fileID, const std::string& name, const fs::path& path) : LgsFile(fileID, name, path) {}
    void generateIR() override;
    ~LgsObjectFile() override;
};


