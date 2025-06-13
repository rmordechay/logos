#pragma once
#include "LgsFile.h"

class LgsObjectFile final : public LgsFile {
public:
    LgsObject *obj = nullptr;

    explicit LgsObjectFile(const string& name, const string& path) : LgsFile(name, path) {}
    Module* generateIR(LgsApp& project) override;
    ~LgsObjectFile() override;
};


