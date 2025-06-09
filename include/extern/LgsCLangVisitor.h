#pragma once

class LgsFile;
class LgsObject;
class LgsType;
struct LgsSymbol;
using namespace clang::tooling;

class LgsCLangVisitor : public clang::RecursiveASTVisitor<LgsCLangVisitor> {
public:
    LgsFile& lgsFile;
    LgsErrHandler& errHandler;
    clang::ASTContext* context;

    explicit LgsCLangVisitor(clang::ASTContext* context, LgsFile& lgsFile, LgsErrHandler& errHandler) : lgsFile(lgsFile), errHandler(errHandler), context(context) {}
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

    explicit LgsCLangASTConsumer(clang::ASTContext* context, LgsFile& lgsFile, LgsErrHandler& errHandler) : visitor(context, lgsFile, errHandler) {}
    void HandleTranslationUnit(clang::ASTContext& context) override;
    ~LgsCLangASTConsumer() override = default;
};
