#ifndef LGSCINTERFACE_H
#define LGSCINTERFACE_H

#include "logos/LgsGlobals.h"
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Tooling/Tooling.h>
#include <memory>

using namespace clang;
using namespace clang::tooling;

LgsType* mapCType(const string& cType);

class LgsCVisitor : public RecursiveASTVisitor<LgsCVisitor> {
public:
    ASTContext* context;

    explicit LgsCVisitor(ASTContext* context) : context(context) {}
    bool VisitFunctionDecl(const FunctionDecl* func) const;
};

class LgsCASTConsumer final : public ASTConsumer {
public:
    LgsCVisitor visitor;

    explicit LgsCASTConsumer(ASTContext* context) : visitor(context) {}
    void HandleTranslationUnit(ASTContext& context) override;
};

class LgsCFrontendAction final : public ASTFrontendAction {
public:
    std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& compilerInstance, StringRef file) override;
};


#endif //LGSCINTERFACE_H
