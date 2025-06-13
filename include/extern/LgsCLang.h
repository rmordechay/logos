#pragma once
#include "data/LgsDefinitions.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "logos/Platform.h"

class LgsFile;
using namespace clang::driver;

class LgsCLang {
public:
    IntrusiveRefCntPtr<vfs::FileSystem> fs;
    path clibRoot;
    path buildDir;
    path outputFilePath = buildDir / "c.o";
    vector<string> compileArgs{CLANG_BINARY, "-c", "-isysroot", clibRoot};

    LgsCLang(const path& clibRoot, const path& buildDir) : clibRoot(clibRoot), buildDir(buildDir) {}
    void getClibRoot() const;
    void parse(LgsFile& lgsFile, LgsErrHandler& errHandler) const;
    void compile(const vector<LgsStrConst*>& files);
    ~LgsCLang() = default;
};
