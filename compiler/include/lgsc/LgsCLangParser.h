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

class LgsCLangParser final : public clang::RecursiveASTVisitor<LgsCLangParser>, public clang::ASTConsumer {
public:
    LgsSymbolTable table;
    LgsErrHandler errHandler;
    clang::ASTContext* context = nullptr;
    int recursionDepth = 0;

    void HandleTranslationUnit(clang::ASTContext& clangContext) override;
    bool VisitFunctionDecl(const clang::FunctionDecl* func);
    bool VisitRecordDecl(const clang::RecordDecl* record);
    LgsType* mapCType(clang::QualType type);
    LgsObject* mapCRecord(const clang::RecordDecl* record);
    LgsType* mapCArray(clang::QualType type);
    LgsType* mapCStruct(clang::QualType type);
    LgsType* mapCFunc(clang::QualType type);
};

