#pragma once
#include "LgsSymbolTable.h"
#include "configs/LgsErrors.h"
#include "../codegen/LgsCodeGen.h"

class LgsRuntime;
class LgsStrConst;
class LgsApp;

class LgsFile {
public:
    size_t id = 0;
    std::string name;
    fs::path path;
    LgsCodeGen generator;
    LgsSymbolTable symbolTable;
    LgsRuntime* runtime = nullptr;
    LgsLocation location{0, 0, 0};
    std::vector<LgsStrConst*> externalCPaths;

    explicit LgsFile(const size_t fileID, const std::string& name, const fs::path& path) : id(fileID), name(name), path(path) {}
    virtual json::value asJSON();
    virtual void format();
    virtual ~LgsFile() = default;
};

inline json::value LgsFile::asJSON() {
    assert(0);
}

inline void LgsFile::format() {
    assert(false);
}
