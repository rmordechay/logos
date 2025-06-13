#pragma once
#include "LgsFile.h"

class LgsObjectFile final : public LgsFile {
public:
    LgsObject *obj = nullptr;

    explicit LgsObjectFile(const string& name, path& path) : LgsFile(name, path) {}
    Module* generateIR() override;
    ~LgsObjectFile() override;
};


