#pragma once
#include "utils/LgsErrHandler.h"
#include "logos/Platform.h"

class LgsStrConst;
class LgsFile;

class LgsCLang {
public:
    LgsPaths& paths;
    vector<string> headers;
    LgsErrHandler errHandler;

    explicit LgsCLang(LgsPaths& paths) : paths(paths) {}
    void setCHeaderPaths();
    string getCode(const LgsStrConst* filePath);
    void parseFile(const string& filePath);
    void compile(const vector<LgsStrConst*>& files) const;
    void getClibRoot() const;
    bool isCLibHeader(const path& cLibPath);
    void setCompileArgs(const vector<LgsStrConst*>& files, vector<const char*>& args) const;
    ~LgsCLang() = default;
};

using namespace clang::driver;