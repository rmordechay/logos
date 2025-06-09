#pragma once
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Tooling/Tooling.h>

class LgsObject;
class LgsType;
struct LgsSymbol;
using namespace clang::tooling;

class LgsCLangVisitor : public clang::RecursiveASTVisitor<LgsCLangVisitor> {
public:
    clang::ASTContext* context;
    LgsErrHandler& errHandler;

    explicit LgsCLangVisitor(clang::ASTContext* context, LgsErrHandler& errHandler) : context(context), errHandler(errHandler) {}
    bool VisitFunctionDecl(const clang::FunctionDecl* func);
    bool VisitRecordDecl(const clang::RecordDecl* record);
    LgsType* mapCType(clang::QualType type);
    LgsObject* mapCRecord(const clang::RecordDecl* record);
    LgsType* mapCArray(clang::QualType type);
    LgsType* mapCStruct(clang::QualType type);
    LgsType* mapCFunc(clang::QualType type);
    bool isValid(clang::SourceLocation loc) const;
    bool isConstCharPointer(clang::QualType qt) const;
    ~LgsCLangVisitor() = default;
};

class LgsCLangASTConsumer final : public clang::ASTConsumer {
public:
    LgsCLangVisitor visitor;

    explicit LgsCLangASTConsumer(clang::ASTContext* context, LgsErrHandler& errHandler) : visitor(context, errHandler) {}
    void HandleTranslationUnit(clang::ASTContext& context) override {
        visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
    ~LgsCLangASTConsumer() override = default;
};

class LgsCLangFeAction final : public clang::ASTFrontendAction {
public:
    LgsErrHandler& errHandler;

    explicit LgsCLangFeAction(LgsErrHandler& errHandler) : errHandler(errHandler) {}
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compilerInstance, StringRef file) override {
        return std::make_unique<LgsCLangASTConsumer>(&compilerInstance.getASTContext(), errHandler);
    }
    ~LgsCLangFeAction() override = default;
};
