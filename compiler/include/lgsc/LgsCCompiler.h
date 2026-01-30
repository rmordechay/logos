#pragma once
#include "LgsCLangParser.h"
#include "LgsSymbolTable.h"
#include "logos/LgsPaths.h"
#include <clang/Basic/Diagnostic.h>
#include <clang/Frontend/CompilerInstance.h>

class LgsStrConst;
class LgsFile;

class LgsDiagnosticConsumer final : public clang::DiagnosticConsumer {
public:
    void HandleDiagnostic(clang::DiagnosticsEngine::Level level, const clang::Diagnostic& info) override;
};

class LgsCCompiler final {
public:
    LgsPaths& paths;
    LgsCLangParser parser;
    clang::CompilerInstance compiler;

    explicit LgsCCompiler(LgsPaths& paths): paths(paths) {
        initCompiler();
    }
    bool parseFile(const fs::path& headerPath);
    void initCompiler();
};

class LgsPPCallbacks final : public clang::PPCallbacks {
public:
    LgsSymbolTable& symbolTable;
    LgsErrHandler errHandler;
    clang::LangOptions &LangOpts;
    clang::SourceManager& sourceManager;
    clang::Preprocessor& preprocessor;

    LgsPPCallbacks(LgsSymbolTable& table, clang::Preprocessor& preprocessor, clang::LangOptions& langOpts, clang::SourceManager& sourceManager) :
        symbolTable(table), LangOpts(langOpts), sourceManager(sourceManager), preprocessor(preprocessor) {
    }

    void MacroDefined(const clang::Token &macroNameToken, const clang::MacroDirective *macroDirective) override;
};