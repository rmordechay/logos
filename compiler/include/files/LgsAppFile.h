#pragma once
#include <filesystem>
#include <string>
#include <vector>

#include "LgsFile.h"
#include "exprs/LgsVariable.h"
#include "stmts/LgsVarDec.h"
#include "LgsVersion.h"
#include "codegen/LgsCodeGen.h"

class LgsStrConst;
class LgsVarDec;
class LgsVariable;

struct LgsImportPkg {
    std::string name = "";
    std::string path = "";
    LgsVersion version = {0, 0, 0};
    LgsVariable* alias = nullptr;
};

class LgsAppFile final : public LgsFile {
public:
    std::vector<LgsVarDec*> configs;
    std::vector<LgsVarDec*> requiredEnvs;
    std::vector<LgsImportPkg> packages;
    std::vector<LgsStrConst*> searchPaths;
    std::vector<LgsStrConst*> libs;

    explicit LgsAppFile(const fs::path& path) : LgsFile(path, CG_MODE_SRC) {}
    size_t hashFile() override;
    ~LgsAppFile() override;
};
