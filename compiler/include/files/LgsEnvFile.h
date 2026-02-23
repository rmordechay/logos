#pragma once
#include <filesystem>
#include <string>
#include <vector>

#include "LgsFile.h"
#include "stmts/LgsVarDec.h"
#include "codegen/LgsCodeGen.h"

class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    std::string name;
    std::vector<LgsVarDec*> varDecs;

    explicit LgsEnvFile(const fs::path& path) : LgsFile(path, CG_MODE_SRC) {}
    size_t hashFile() override;
    ~LgsEnvFile() override;
};

