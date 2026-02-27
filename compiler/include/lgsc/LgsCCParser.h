#pragma once
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Tooling/Tooling.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Lex/PPCallbacks.h>

#include "LgsSymbolTable.h"
#include "errors/LgsErrHandler.h"

struct LgsSymbolTable;
class LgsErrHandler;
class LgsFile;
class LgsObject;
class LgsType;
struct LgsSymbol;
namespace clang {
class CompilerInstance;
class FunctionDecl;
class QualType;
class RecordDecl;
class TypedefDecl;
}  // namespace clang

class LgsCCParser final : public clang::RecursiveASTVisitor<LgsCCParser> {
public:
    LgsSymbolTable symbolTable;
    LgsErrHandler errHandler;
    int recursionDepth = 0;

    bool VisitFunctionDecl(clang::FunctionDecl* func);
    bool VisitRecordDecl(const clang::RecordDecl* record);
    bool VisitTypedefDecl(const clang::TypedefDecl* typedefDecl);
    LgsType* mapCType(clang::QualType type);
    LgsObject* mapCRecord(const clang::RecordDecl* record);
    LgsType* mapCArray(clang::QualType type);
    LgsType* mapCStruct(clang::QualType type);
    LgsType* mapCFunc(clang::QualType type);
};

class LgsCCAstConsumer final : public clang::ASTConsumer {
public:
    LgsCCParser& parser;

    explicit LgsCCAstConsumer(LgsCCParser& parser): parser(parser) {}
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
