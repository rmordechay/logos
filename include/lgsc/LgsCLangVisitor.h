#pragma once
#include "files/LgsFile.h"
#include "utils/LgsErrHandler.h"
#include "utils/LgsUtils.h"
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

class LgsErrHandler;
class LgsFile;
class LgsObject;
class LgsType;
struct LgsSymbol;

class LgsCLangVisitor final : public clang::RecursiveASTVisitor<LgsCLangVisitor>, public clang::ASTConsumer {
public:
    LgsFile* file;
    LgsErrHandler errHandler;
    clang::ASTContext* context = nullptr;
    int recursionDepth = 0;

    explicit LgsCLangVisitor(LgsFile* file) : file(file) {}
    void HandleTranslationUnit(clang::ASTContext& clangContext) override;
    bool VisitFunctionDecl(const clang::FunctionDecl* func);
    bool VisitRecordDecl(const clang::RecordDecl* record);
    LgsType* mapCType(clang::QualType type);
    LgsObject* mapCRecord(const clang::RecordDecl* record);
    LgsType* mapCArray(clang::QualType type);
    LgsType* mapCStruct(clang::QualType type);
    LgsType* mapCFunc(clang::QualType type);
    ~LgsCLangVisitor() override = default;
};

class LgsCLangFeAction final : public clang::ASTFrontendAction {
public:
    LgsFile* file;

    explicit LgsCLangFeAction(LgsFile* file) : file(file) {}
    unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compilerInstance, StringRef inFile) override {
        return make_unique<LgsCLangVisitor>(file);
    }
    ~LgsCLangFeAction() override = default;
};
