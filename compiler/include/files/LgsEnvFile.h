#pragma once
#include "LgsFile.h"
#include "stmts/LgsVarDec.h"

class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    std::string name;
    std::vector<LgsVarDec*> varDecs;

    LgsEnvFile(const fs::path& path) : LgsFile(path) {}
    size_t hashFile() override;
    ~LgsEnvFile() override;
};

