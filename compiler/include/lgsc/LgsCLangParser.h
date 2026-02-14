#pragma once
#include "LgsSymbolTable.h"
#include "errors/LgsErrHandler.h"
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Tooling/Tooling.h>

struct LgsSymbolTable;
class LgsErrHandler;
class LgsFile;
class LgsObject;
class LgsType;
struct LgsSymbol;

class LgsCLangParser final : public clang::RecursiveASTVisitor<LgsCLangParser> {
public:
    LgsSymbolTable symbolTable;
    LgsErrHandler errHandler;
    int recursionDepth = 0;

    bool VisitFunctionDecl(const clang::FunctionDecl* func);
    bool VisitRecordDecl(const clang::RecordDecl* record);
    bool VisitTypedefDecl(const clang::TypedefDecl* typedefDecl);
    LgsType* mapCType(clang::QualType type);
    LgsObject* mapCRecord(const clang::RecordDecl* record);
    LgsType* mapCArray(clang::QualType type);
    LgsType* mapCStruct(clang::QualType type);
    LgsType* mapCFunc(clang::QualType type);
};

class LgsCLangASTConsumer final : public clang::ASTConsumer {
public:
    LgsCLangParser& parser;

    explicit LgsCLangASTConsumer(LgsCLangParser& parser): parser(parser) {}
    void HandleTranslationUnit(clang::ASTContext& clangContext) override;
};

class LgsPPCallbacks final : public clang::PPCallbacks {
public:
    LgsErrHandler errHandler;
    LgsSymbolTable& symbolTable;
    clang::CompilerInstance& compiler;

    LgsPPCallbacks(LgsSymbolTable& symbolTable, clang::CompilerInstance& compiler): symbolTable(symbolTable), compiler(compiler) {}
    void MacroDefined(const clang::Token &macroNameToken, const clang::MacroDirective *macroDirective) override;
};
