#pragma once
#include "logos/LgsModule.h"

class LgsStrConst;
class LgsApp;
class LgsModule;

class LgsFile {
public:
    string name;
    path absPath;
    streampos pos = 0;
    streampos pathIndex = 0;
    LgsSymbolTable symbolTable;
    vector<LgsStrConst*> externFiles;

    explicit LgsFile(const string& name, const path& path) : name(name), absPath(path) {}
    virtual LgsModule* generateIR(LgsSymbolTable& globals);
    virtual void format();
    virtual ~LgsFile() = default;
};

// Only files that need generation implement this func.
inline LgsModule* LgsFile::generateIR(LgsSymbolTable& globals) {
    return nullptr;
}

inline void LgsFile::format() {
    assert(false);
}
