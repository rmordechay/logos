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
    ~LgsAppConfigFile() override;
};

inline LgsAppConfigFile::~LgsAppConfigFile() {
    for (const auto varDec : configs) {
        delete varDec;
    }
    configs.clear();
    for (const auto& package : packages) {
        freeExpr(package.alias);
    }
    packages.clear();
    for (const auto requiredEnv : requiredEnvs) {
        freeExpr(requiredEnv);
    }
    requiredEnvs.clear();
}
