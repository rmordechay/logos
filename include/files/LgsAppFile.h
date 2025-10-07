#pragma once
#include "LgsFile.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsVarDec.h"

class LgsVarDec;

class LgsAppFile final : public LgsFile {
public:
    std::vector<LgsVarDec*> requireEnvVars;
    std::vector<std::string> requirePackages;

    explicit LgsAppFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    ~LgsAppFile() override;
};

inline LgsAppFile::~LgsAppFile() {
    for (const auto varDec : requireEnvVars) {
        delete varDec;
    }
    requireEnvVars.clear();
}
