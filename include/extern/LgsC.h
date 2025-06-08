#pragma once
#include "exprs/unary/constants/LgsStrConst.h"
#include <clang/Basic/Diagnostic.h>
#include <clang/Frontend/CompilerInstance.h>

using namespace llvm;

struct LgsDiagnosticsConsumer final : clang::DiagnosticConsumer {
    std::string message;
    raw_string_ostream os{message};
    void HandleDiagnostic(clang::DiagnosticsEngine::Level diagLevel, const clang::Diagnostic& info) override;
};

class LgsC {
public:
    LgsErrHandler& errHandler;
    LgsDiagnosticsConsumer dc;
    IntrusiveRefCntPtr<vfs::FileSystem> fs;

    explicit LgsC(LgsErrHandler& errHandler) : errHandler(errHandler) {}
    void compile(const std::vector<std::string>& files);
    void parse(const vector<LgsStrConst*>& filePaths) const;
    ~LgsC() = default;
};



