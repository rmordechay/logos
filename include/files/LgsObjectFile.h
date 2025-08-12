#pragma once
#include "LgsFile.h"

class LgsObjectFile final : public LgsFile {
public:
    LgsObject *obj = nullptr;

    explicit LgsObjectFile(const string& name, const fs::path& path) : LgsFile(name, path) {}
    void generateIR() override;
    ~LgsObjectFile() override;
};


