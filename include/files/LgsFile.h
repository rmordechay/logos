#pragma once
#include "LgsSymbolTable.h"
#include "data/LgsErrors.h"
#include "../codegen/LgsLLVMGen.h"

class LgsRuntime;
class LgsStrConst;
class LgsApp;

class LgsFile {
public:
    size_t id = 0;
    fs::path path;
    LgsLLVMGen generator;
    LgsLocation location;
    LgsSymbolTable symbolTable;
    LgsRuntime* runtime = nullptr;
    std::vector<LgsStrConst*> externalCPaths;

    explicit LgsFile(const size_t fileID, const fs::path& path) : id(fileID), path(path) {}
    virtual void format();
    virtual ~LgsFile() = default;
};

inline void LgsFile::format() {
    assert(false);
}
