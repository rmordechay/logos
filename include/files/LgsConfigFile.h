#pragma once
#include "LgsFile.h"
#include "stmts/LgsVarDec.h"

class LgsConfigFile final : public LgsFile {
public:
    std::vector<LgsVarDec*> configs;
    std::vector<std::string> packages;

    explicit LgsConfigFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    ~LgsConfigFile() override;
};

inline LgsConfigFile::~LgsConfigFile() {
    for (const auto varDec : configs) {
        delete varDec;
    }
    configs.clear();
}
