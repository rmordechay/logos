#pragma once
#include "LgsFile.h"

class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    std::vector<LgsVarDec*> varDecs;
    LgsEnvFile(const std::string& fileName, const fs::path& path, const std::vector<LgsVarDec*>& varDecs) : LgsFile(fileName, path), varDecs(varDecs) {}
    ~LgsEnvFile() override = default;
};
