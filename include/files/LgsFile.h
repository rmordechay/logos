#pragma once
#include "logos/LgsRuntime.h"

class LgsStrConst;
class LgsApp;
class LgsRuntime;

class LgsFile {
public:
    string name;
    string code;
    string absPath;
    string relPath;
    LgsSymbolTable symbolTable;
    vector<LgsStrConst*> externFiles;

    explicit LgsFile(const string& name, const string& path) : name(name), absPath(path) {}
    virtual Module* generateIR(LgsApp& project);
    virtual void format();
    virtual ~LgsFile() = default;
};

inline Module* LgsFile::generateIR(LgsApp& project) {
    return nullptr;
}

inline void LgsFile::format() {
    assert(false);
}