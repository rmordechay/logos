#pragma once
#include "utils/LgsErrHandler.h"
#include "logos/LgsPaths.h"

class LgsStrConst;
class LgsFile;

class LgsCLang {
public:
    LgsPaths& paths;
    vector<string> headers;
    LgsErrHandler errHandler;

    explicit LgsCLang(LgsPaths& paths) : paths(paths) {}
    void setCHeaderPaths();
    string getCode(LgsStrConst* filePath);
    void parseFile(const string& filePath);
    void compile(const vector<LgsStrConst*>& files) const;
    bool isCLibHeader(const filesystem::path& cLibPath);
    void setCompileArgs(const vector<LgsStrConst*>& files, vector<const char*>& args) const;
    ~LgsCLang() = default;
};
