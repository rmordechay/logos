#pragma once
#include "exprs/unary/constants/LgsStrConst.h"

class LgsFile;
using namespace clang::driver;

class LgsCLang {
public:
    IntrusiveRefCntPtr<vfs::FileSystem> fs;
    path outputFilePath = paths.buildDir / "c.o";
    vector<string> compileArgs{CLANG_BINARY, "-c", "-isysroot", platform.clibRoot};

    void getClibRoot() const;
    void parse(LgsFile& lgsFile, LgsErrHandler& errHandler) const;
    void compile(const vector<LgsStrConst*>& files);
    ~LgsCLang() = default;
};
