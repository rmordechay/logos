#pragma once
#include "logos/LgsErrHandler.h"
#include "logos/Platform.h"

class LgsStrConst;
class LgsFile;

class LgsCLang {
public:
    LgsPaths& paths;
    vector<string> headers;
    LgsErrHandler errHandler;

    explicit LgsCLang(LgsPaths& paths) : paths(paths) {}
    string getCode(const LgsStrConst* filePath);
    bool isCLibHeader(const path& cLibPath);
    void parseFile(const LgsStrConst* filePaths);
    void compile(const vector<LgsStrConst*>& files) const;
    vector<const char*> getCompileArgs(const vector<LgsStrConst*>& files) const;
    void setCHeaderPaths();
    void getClibRoot() const;
    ~LgsCLang() = default;
};

using namespace clang::driver;