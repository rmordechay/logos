#pragma once
#include "exprs/unary/constants/LgsStrConst.h"
#include "files/LgsFile.h"

using namespace clang::driver;

struct LgsDiagnosticsConsumer final : clang::DiagnosticConsumer {
    string message;
    raw_string_ostream os{message};
    void HandleDiagnostic(clang::DiagnosticsEngine::Level diagLevel, const clang::Diagnostic& info) override;
};

class LgsCLangFeAction final : public clang::ASTFrontendAction {
public:
    LgsFile& lgsFile;
    LgsErrHandler& errHandler;

    explicit LgsCLangFeAction(LgsFile& lgsFile, LgsErrHandler& errHandler) : lgsFile(lgsFile), errHandler(errHandler) {}
    unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compilerInstance, StringRef file) override;
    ~LgsCLangFeAction() override = default;
};

class LgsCLang {
public:
    LgsFile& lgsFile;
    LgsErrHandler& errHandler;
    LgsDiagnosticsConsumer dc;
    IntrusiveRefCntPtr<vfs::FileSystem> fs;
    vector<string> compileArgs{"clang", "-c", "-isysroot", platform.clibRoot};
    path outputFilePath = paths.buildDir / "c.o";

    LgsCLang(LgsFile& lgsFile, LgsErrHandler& errHandler) : lgsFile(lgsFile), errHandler(errHandler) {}
    void compile(const vector<string>& files);
    void parse() const;
    ~LgsCLang() = default;
};
