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
    LgsDiagnosticsConsumer dc;
    IntrusiveRefCntPtr<vfs::FileSystem> fs;

    LgsC() {
        fs = vfs::getRealFileSystem();
    }

    void compile(const std::vector<std::string>& files);
    void parse(vector<LgsStrConst*>& filePaths, LgsErrHandler* errHandler) const;
    ~LgsC() = default;
};



