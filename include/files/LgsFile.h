#pragma once
#include "LgsSymbolTable.h"
#include "logos/LgsCodeGen.h"

class LgsStrConst;
class LgsApp;
class LgsCodeGen;

class LgsFile {
public:
    string name;
    fs::path absPath;
    LgsCodeGen codeGen;
    LgsLocation location;
    LgsSymbolTable symbolTable;
    LgsRuntime* runtime = nullptr;
    vector<LgsStrConst*> externalCPaths;

    explicit LgsFile(const string& name, const fs::path& path) : name(name), absPath(path) {}
    virtual void generateIR();
    virtual void format();
    virtual ~LgsFile() = default;
};

inline void LgsFile::generateIR() {}

inline void LgsFile::format() {
    assert(false);
}
