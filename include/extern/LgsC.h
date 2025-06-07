#ifndef LGSC_H
#define LGSC_H

#include "exprs/unary/constants/LgsStrConst.h"
#include "logos/LgsErrHandler.h"

#include <clang/Basic/Diagnostic.h>
#include <llvm/Support/raw_ostream.h>
#include <clang/Frontend/CompilerInstance.h>
#include <string>

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
    void parse(const vector<LgsStrConst*>& filePaths, LgsErrHandler* errHandler) const;
    ~LgsC() = default;
};


#endif //LGSC_H
