#pragma once
#include "logos/LgsPaths.h"
#include "utils/LgsErrHandler.h"

class LgsStrConst;
class LgsFile;

class LgsCLang {
public:
    LgsPaths& paths;
    LgsErrHandler errHandler;

    explicit LgsCLang(LgsPaths& paths) : paths(paths) {}
    void parseFile(const fs::path& fileName, LgsFile* lgsFile) const;
    void compile(const std::vector<LgsStrConst*>& files) const;
    std::vector<const char*> getCompileArgs(const std::vector<LgsStrConst*>& files) const;
    fs::path resolveExternalFile(LgsStrConst* filePath);
    void resolveCFiles(LgsFile* lgsFile);
    ~LgsCLang() = default;
};
