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
    fs::path path;
    LgsLLVMGen cg;
    LgsLocation location;
    LgsSymbolTable symbolTable;

    explicit LgsFile(const size_t fileID, const fs::path& path) : id(fileID), path(path) {}
    virtual size_t hashFile() = 0;
    virtual ~LgsFile() = default;
};
