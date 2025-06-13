#pragma once
#include "logos/LgsRuntime.h"

class LgsStrConst;
class LgsApp;
class LgsRuntime;

class LgsFile {
public:
    string name;
    string code;
    path& absPath;
    LgsSymbolTable symbolTable;
    vector<LgsStrConst*> externFiles;

    explicit LgsFile(const string& name, path& path) : name(name), absPath(path) {}
    virtual Module* generateIR();
    virtual void format();
    virtual ~LgsFile();
};

inline Module* LgsFile::generateIR() {
    return nullptr;
}

inline void LgsFile::format() {
    assert(false);
}

inline LgsFile::~LgsFile() {
    delete &absPath;
}
