#pragma once
#include "data/LgsDefinitions.h"
#include "exprs/unary/constants/LgsStrConst.h"

class LgsFile;
using namespace clang::driver;

class LgsCLang {
public:
    path clibRoot;
    path buildDir;
    path outputFilePath = buildDir / "c.o";
    IntrusiveRefCntPtr<vfs::FileSystem> fs;
    vector<string> compileArgs{CLANG_BINARY, "-c", "-isysroot", clibRoot};

    LgsCLang(const path& clibRoot, const path& buildDir) : clibRoot(clibRoot), buildDir(buildDir) {}
    void getClibRoot() const;
    void parse(LgsFile& lgsFile, LgsErrHandler& errHandler) const;
    void compile(const vector<LgsStrConst*>& files);
    ~LgsCLang() = default;
};
