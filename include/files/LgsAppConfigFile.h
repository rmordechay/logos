#pragma once
#include "LgsFile.h"
#include "exprs/LgsVariable.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

struct LgsImportPackage {
    std::string name;
    std::string version;
    LgsVariable* alias;
};

class LgsAppConfigFile final : public LgsFile {
public:
    std::vector<LgsVarDec*> configs;
    std::vector<LgsImportPackage> packages;
    std::vector<LgsVariable*> requiredEnvs;

    explicit LgsAppConfigFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    size_t hashFile() override;
    ~LgsAppConfigFile() override;
};

