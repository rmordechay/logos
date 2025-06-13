#pragma once

class LgsErrHandler;
class LgsFile;
class LgsObject;
class LgsType;
struct LgsSymbol;
using namespace clang::tooling;

class LgsCLangVisitor : public clang::RecursiveASTVisitor<LgsCLangVisitor> {
public:
    bool VisitFunctionDecl(const clang::FunctionDecl* func);
    bool VisitRecordDecl(const clang::RecordDecl* record);
    LgsType* mapCType(clang::QualType type);
    LgsObject* mapCRecord(const clang::RecordDecl* record);
    LgsType* mapCArray(clang::QualType type);
    LgsType* mapCStruct(clang::QualType type);
    LgsType* mapCFunc(clang::QualType type);
    bool isConstCharPointer(clang::QualType qt) const;
    ~LgsCLangVisitor() = default;
};

class LgsCLangASTConsumer final : public clang::ASTConsumer {
public:
    LgsCLangVisitor visitor;

    void HandleTranslationUnit(clang::ASTContext& context) override {
        visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
    ~LgsCLangASTConsumer() override = default;
};

class LgsCLangFeAction final : public clang::ASTFrontendAction {
public:
    unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compilerInstance, StringRef file) override {
        return make_unique<LgsCLangASTConsumer>();
    }
    ~LgsCLangFeAction() override = default;
};
