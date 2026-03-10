#include "files/LgsAppFile.h"

#include "LgsUtils.h"
#include "exprs/constants/LgsStrConst.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsVariable.h"
#include "stmts/LgsStmt.h"
#include "stmts/LgsVarDec.h"

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
