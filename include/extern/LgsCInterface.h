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
    bool isConstCharPointer(QualType qt) const;
    LgsType* mapCType(QualType type);
    LgsObject* createLgsObj(const RecordDecl* record);
    bool isValid(SourceLocation loc) const;
    bool VisitFunctionDecl(const FunctionDecl* func);
    bool VisitRecordDecl(const RecordDecl* record);
    ~LgsCVisitor() = default;
};

class LgsCASTConsumer final : public ASTConsumer {
public:
    LgsCVisitor visitor;

    explicit LgsCASTConsumer(ASTContext* context) : visitor(context) {}
    void HandleTranslationUnit(ASTContext& context) override;
    ~LgsCASTConsumer() override = default;
};

class LgsCFrontendAction final : public ASTFrontendAction {
public:
    std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& compilerInstance, StringRef file) override;
    ~LgsCFrontendAction() override = default;
};


#endif //LGSCINTERFACE_H
