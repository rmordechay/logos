#pragma once
#include "LgsFile.h"

class LgsObjectFile final : public LgsFile {
public:
    LgsObject *obj = nullptr;

    explicit LgsObjectFile(const string& name, const path& path) : LgsFile(name, path) {}
    LgsModule* generateIR(LgsSymbolTable& globals) override;
    ~LgsObjectFile() override;
};


