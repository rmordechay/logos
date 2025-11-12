#pragma once
#include "LgsCLangParser.h"
#include "LgsSymbolTable.h"
#include "logos/LgsPaths.h"
#include <clang/Basic/Diagnostic.h>

class LgsStrConst;
class LgsFile;

class LgsDiagnosticConsumer final : public clang::DiagnosticConsumer {
public:
    void HandleDiagnostic(clang::DiagnosticsEngine::Level level, const clang::Diagnostic& info) override;
};

class LgsCLang final {
public:
    LgsSymbolTable table;
    fs::path cLibHeadersDir;

    explicit LgsCLang(const fs::path& cLibHeadersDir): cLibHeadersDir(cLibHeadersDir) {}
    bool parseFile(LgsCLangParser& parser, const std::string& cCode);
};
