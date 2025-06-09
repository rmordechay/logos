#pragma once
#include "exprs/unary/constants/LgsStrConst.h"
#include <clang/Basic/Diagnostic.h>
#include <clang/Frontend/CompilerInstance.h>

struct LgsDiagnosticsConsumer final : clang::DiagnosticConsumer {
    string message;
    raw_string_ostream os{message};
    void HandleDiagnostic(clang::DiagnosticsEngine::Level diagLevel, const clang::Diagnostic& info) override;
};

class LgsCLang {
public:
    LgsErrHandler& errHandler;
    LgsDiagnosticsConsumer dc;
    IntrusiveRefCntPtr<vfs::FileSystem> fs;

    explicit LgsCLang(LgsErrHandler& errHandler) : errHandler(errHandler) {}
    void compile(const vector<string>& files);
    void getClibRoot() const;
    void parse(const vector<LgsStrConst*>& filePaths) const;
    ~LgsCLang() = default;
};
