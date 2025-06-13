#pragma once
#include "logos/Platform.h"

class LgsErrHandler;
class LgsStrConst;
class LgsFile;

class LgsCLang {
public:
    void getClibRoot() const;
    string getCode(const LgsStrConst* filePath, const LgsPaths& paths, LgsErrHandler& errHandler) const;
    void parseFile(const LgsStrConst* filePath, const LgsPaths& paths, LgsErrHandler& errHandler) const;
    void compile(const vector<LgsStrConst*>& files, const LgsPaths& paths) const;
    vector<const char*> getCompileArgs(const vector<LgsStrConst*>& files, const LgsPaths& paths) const;
    ~LgsCLang() = default;
};

using namespace clang::driver;