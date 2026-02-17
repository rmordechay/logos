#include "files/LgsAppFile.h"

#include "exprs/constants/LgsStrConst.h"

size_t LgsAppFile::hashFile() {
    size_t hash = 0;
    HASH_VECTOR(configs, hash);
    HASH_VECTOR(requiredEnvs, hash);
    return hash;
}

LgsAppFile::~LgsAppFile() {
    for (const auto varDec : configs) {
        freeStmt(varDec);
    }
    configs.clear();
    for (const auto& package : packages) {
        freeExpr(package.alias);
    }
    packages.clear();
    for (const auto requiredEnv : requiredEnvs) {
        freeStmt(requiredEnv);
    }
    requiredEnvs.clear();
    for (const auto searchPath : searchPaths) {
        freeExpr(searchPath);
    }
    searchPaths.clear();
}
