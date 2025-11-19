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
    fs::path cLibHeadersDir;

    explicit LgsCLang(const fs::path& cLibHeadersDir): cLibHeadersDir(cLibHeadersDir) {}
    bool parseFile(LgsCLangParser& parser, const fs::path& headerPath) const;
};


class LgsPPCallbacks final : public clang::PPCallbacks {
public:
    LgsSymbolTable& table;
    LgsErrHandler errHandler;
    clang::LangOptions &LangOpts;
    clang::SourceManager& sourceManager;
    clang::Preprocessor& preprocessor;

    LgsPPCallbacks(LgsSymbolTable& table, clang::Preprocessor& preprocessor, clang::LangOptions& langOpts, clang::SourceManager& sourceManager) :
        table(table), LangOpts(langOpts), sourceManager(sourceManager), preprocessor(preprocessor) {
    }

    void MacroDefined(const clang::Token &macroNameToken, const clang::MacroDirective *macroDirective) override;
};
