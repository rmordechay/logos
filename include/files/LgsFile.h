#pragma once

class LgsStrConst;
class LogosProject;
class LgsRuntime;

using namespace nlohmann;

class LgsFile {
public:
    string name;
    string code;
    string absPath;
    string relPath;
    LgsSymbolTable symbolTable;
    vector<LgsStrConst*> externFiles;

    explicit LgsFile(const string& name, const string& path) : name(name), absPath(path) {}
    virtual Module* generateIR(LogosProject& project);
    virtual void format();
    virtual json asJSON();
    virtual ~LgsFile() = default;
};

inline Module* LgsFile::generateIR(LogosProject& project) {
    return nullptr;
}

inline void LgsFile::format() {
    assert(false);
}

inline json LgsFile::asJSON() {
    assert(false);
}


