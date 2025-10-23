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
    fs::path filePath;
    LgsLLVMGen generator;
    LgsLocation location;
    LgsSymbolTable symbolTable;
    std::vector<LgsStrConst*> externalCPaths;

    explicit LgsFile(const size_t fileID, const fs::path& path) : id(fileID), filePath(path) {}
    virtual size_t hashFile();
    virtual ~LgsFile() = default;
};

inline size_t LgsFile::hashFile() {
    assert(0);
}
