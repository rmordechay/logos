#pragma once
#include "utils/LgsErrHandler.h"
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Tooling/Tooling.h>

class LgsErrHandler;
class LgsFile;
class LgsObject;
class LgsType;
struct LgsSymbol;

class LgsCLangParser final : public clang::RecursiveASTVisitor<LgsCLangParser>, public clang::ASTConsumer {
public:
    LgsFile* lgsFile;
    LgsErrHandler errHandler;
    clang::ASTContext* context = nullptr;
    int recursionDepth = 0;

    explicit LgsCLangParser(LgsFile* lgsFile) : lgsFile(lgsFile) {}
    void HandleTranslationUnit(clang::ASTContext& clangContext) override;
    bool VisitFunctionDecl(const clang::FunctionDecl* func);
    bool VisitRecordDecl(const clang::RecordDecl* record);
    LgsType* mapCType(clang::QualType type);
    LgsObject* mapCRecord(const clang::RecordDecl* record);
    LgsType* mapCArray(clang::QualType type);
    LgsType* mapCStruct(clang::QualType type);
    LgsType* mapCFunc(clang::QualType type);
};

