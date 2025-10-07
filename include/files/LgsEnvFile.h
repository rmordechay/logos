#pragma once
#include "LgsFile.h"
#include "stmts/LgsVarDec.h"

class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    std::string envName;
    std::vector<LgsVarDec*> varDecs;

    LgsEnvFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    ~LgsEnvFile() override;
};

inline LgsEnvFile::~LgsEnvFile() {
    for (const auto varDec : varDecs) {
        delete varDec;
    }
    varDecs.clear();
}
