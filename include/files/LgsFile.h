#pragma once
#include "LgsSymbolTable.h"
#include "data/LgsErrors.h"
#include "codegen/LgsLLVMGen.h"

namespace fs = std::filesystem;
class LgsStrConst;
class LgsApp;

class LgsFile {
public:
    size_t id = 0;
    fs::path absPath;
    LgsLLVMGen cg;
    LgsLocation location;
    LgsSymbolTable symbolTable;
    std::vector<LgsStrConst*> externalCPaths;

    explicit LgsFile(const size_t fileID, const fs::path& path) : id(fileID), absPath(path) {}
    virtual size_t hashFile() = 0;
    virtual ~LgsFile() = default;
};
