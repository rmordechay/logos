#pragma once
#include "logos/LgsModule.h"

class LgsStrConst;
class LgsApp;
class LgsModule;

class LgsFile {
public:
    string name;
    path absPath;
    LgsSymbolTable symbolTable;
    vector<LgsStrConst*> externFiles;

    explicit LgsFile(const string& name, const path& path) : name(name), absPath(path) {}
    virtual LgsModule* generateIR();
    virtual void format();
    virtual ~LgsFile();
};

// Only files that need generation implement this func.
inline LgsModule* LgsFile::generateIR() {
    return nullptr;
}

inline void LgsFile::format() {
    assert(false);
}

inline LgsFile::~LgsFile() {
    delete &absPath;
}
