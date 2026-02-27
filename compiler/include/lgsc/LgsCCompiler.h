#pragma once
#include <clang/Basic/Diagnostic.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <filesystem>

#include "LgsCCParser.h"
#include "logos/LgsPaths.h"

class LgsStrConst;
class LgsFile;

class LgsCCompiler final {
public:
    LgsPaths& paths;
    LgsCCParser parser;
    clang::CompilerInstance compiler;

    explicit LgsCCompiler(LgsPaths& paths): paths(paths) {}
    bool parseFile(const fs::path& headerPath);
};

class LgsParseAction : public clang::ASTFrontendAction {
public:
    LgsCCParser& parser;

    explicit LgsParseAction(LgsCCParser& parser): parser(parser) {}
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &ci, llvm::StringRef inFile) override;
};

class LgsDiagnosticConsumer final : public clang::DiagnosticConsumer {
public:
    void HandleDiagnostic(clang::DiagnosticsEngine::Level level, const clang::Diagnostic& info) override;
};
