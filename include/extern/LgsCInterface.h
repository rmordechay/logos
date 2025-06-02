#ifndef LGSCINTERFACE_H
#define LGSCINTERFACE_H


#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Tooling/Tooling.h>
#include <memory>

class LgsObject;
struct LgsSymbol;
class LgsType;
using namespace clang::tooling;

class LgsCVisitor : public clang::RecursiveASTVisitor<LgsCVisitor> {
public:
    clang::ASTContext* context;

    explicit LgsCVisitor(clang::ASTContext* context) : context(context) {}
    bool isConstCharPointer(clang::QualType qt) const;
    LgsType* mapCType(clang::QualType type);
    LgsSymbol* getSymbol(const std::string& name) const;
    LgsObject* createLgsObj(const clang::RecordDecl* record);
    bool isValid(clang::SourceLocation loc) const;
    bool VisitFunctionDecl(const clang::FunctionDecl* func);
    bool VisitRecordDecl(const clang::RecordDecl* record);
    ~LgsCVisitor() = default;
};

class LgsCASTConsumer final : public clang::ASTConsumer {
public:
    LgsCVisitor visitor;

    explicit LgsCASTConsumer(clang::ASTContext* context) : visitor(context) {}
    void HandleTranslationUnit(clang::ASTContext& context) override {
        visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
    ~LgsCASTConsumer() override = default;
};

class LgsCFrontendAction final : public clang::ASTFrontendAction {
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compilerInstance, llvm::StringRef file) override {
        return std::make_unique<LgsCASTConsumer>(&compilerInstance.getASTContext());
    }
    ~LgsCFrontendAction() override = default;
};


#endif //LGSCINTERFACE_H
