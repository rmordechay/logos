#pragma once
#include "LgsSymbolTable.h"
#include "logos/LgsCodeGen.h"
#include "configs/LgsErrors.h"

class LgsStrConst;
class LgsApp;
class LgsCodeGen;

class LgsFile {
public:
    size_t id = 0;
    std::string name;
    fs::path absPath;
    LgsCodeGen codeGen;
    LgsSymbolTable symbolTable;
    LgsRuntime* runtime = nullptr;
    LgsLocation location{0, 0, 0};
    std::vector<LgsStrConst*> externalCPaths;

    explicit LgsFile(const size_t fileID, const std::string& name, const fs::path& path) : id(fileID), name(name), absPath(path) {}
    virtual json::object asJSON();
    virtual void generateIR();
    virtual void format();
    virtual ~LgsFile() = default;
};

inline json::object LgsFile::asJSON() {
    assert(0);
}

inline void LgsFile::generateIR() {}

inline void LgsFile::format() {
    assert(false);
}
