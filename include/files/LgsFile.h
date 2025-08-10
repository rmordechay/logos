#pragma once
#include "LgsSymbolTable.h"
#include "logos/LgsCodeGen.h"

class LgsStrConst;
class LgsApp;
class LgsCodeGen;

class LgsFile {
public:
    string name;
    LgsCodeGen codeGen;
    LgsLocation location;
    filesystem::path absPath;
    LgsSymbolTable symbolTable;
    vector<LgsStrConst*> externFiles;

    explicit LgsFile(const string& name, const filesystem::path& path) : name(name), absPath(path) {}
    virtual void generateIR();
    virtual void format();
    virtual ~LgsFile() = default;
};

inline void LgsFile::generateIR() {}

inline void LgsFile::format() {
    assert(false);
}
