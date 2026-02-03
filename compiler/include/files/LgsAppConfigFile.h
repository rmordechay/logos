#pragma once
#include "LgsFile.h"
#include "exprs/LgsVariable.h"
#include "logos/LgsAppConfigs.h"
#include "stmts/LgsVarDec.h"

struct LgsImportPackage {
    std::string name = "";
    std::string url = "";
    LgsVersion version = {0, 0, 0};
    LgsVariable* alias = nullptr;
};

class LgsAppConfigFile final : public LgsFile {
public:
    std::vector<LgsVarDec*> configs;
    std::vector<LgsVarDec*> requiredEnvs;
    std::vector<LgsImportPackage> packages;
    std::vector<LgsStrConst*> searchPaths;

    explicit LgsAppConfigFile(const fs::path& path) : LgsFile(path, CG_MODE_SRC_CODE) {}
    size_t hashFile() override;
    ~LgsAppConfigFile() override;
};
