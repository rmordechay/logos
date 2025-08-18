#pragma once
#include "LgsFile.h"
#include "stmts/LgsVarDec.h"

class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    std::vector<LgsVarDec*> varDecs;

    LgsEnvFile(const size_t fileID, const std::string& fileName, const fs::path& path, const std::vector<LgsVarDec*>& varDecs) : LgsFile(fileID, fileName, path), varDecs(varDecs) {}
    ~LgsEnvFile() override;
};

inline LgsEnvFile::~LgsEnvFile() {
    for (const auto varDec : varDecs) {
        delete varDec;
    }
    varDecs.clear();
}
