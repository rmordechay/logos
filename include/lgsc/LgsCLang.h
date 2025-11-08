#pragma once
#include "logos/LgsPaths.h"
#include "utils/LgsErrHandler.h"
#include <clang/Basic/Diagnostic.h>

class LgsStrConst;
class LgsFile;

class LgsDiagnosticConsumer final : public clang::DiagnosticConsumer {
public:
    void HandleDiagnostic(clang::DiagnosticsEngine::Level level, const clang::Diagnostic& info) override;
};

class LgsCLang final {
public:
    LgsPaths& paths;
    LgsErrHandler errHandler;

    explicit LgsCLang(LgsPaths& paths) : paths(paths) {}
    bool parseFile(const fs::path& fileName, LgsFile* lgsFile);
};
