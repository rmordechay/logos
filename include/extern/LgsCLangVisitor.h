#pragma once
#include "files/LgsFile.h"
#include "utils/LgsUtils.h"

class LgsErrHandler;
class LgsFile;
class LgsObject;
class LgsType;
struct LgsSymbol;
using namespace clang::tooling;

class LgsCLangVisitor : public clang::RecursiveASTVisitor<LgsCLangVisitor> {
public:
    LgsFile* cFile;

    explicit LgsCLangVisitor(path& filePath) : cFile(new LgsFile(filePath.filename(), filePath)) {}
    bool VisitFunctionDecl(const clang::FunctionDecl* func);
    bool VisitRecordDecl(const clang::RecordDecl* record);
    LgsType* mapCType(clang::QualType type);
    LgsObject* mapCRecord(const clang::RecordDecl* record);
    LgsType* mapCArray(clang::QualType type);
    LgsType* mapCStruct(clang::QualType type);
    LgsType* mapCFunc(clang::QualType type);
    bool isConstCharPointer(clang::QualType qt) const;
    bool isLgsKeyword(const string& s) const;
    ~LgsCLangVisitor() = default;
};

class LgsCLangASTConsumer final : public clang::ASTConsumer {
public:
    LgsCLangVisitor visitor;

    explicit LgsCLangASTConsumer(path& filePath) : visitor(filePath) {}
    void HandleTranslationUnit(clang::ASTContext& context) override;
    ~LgsCLangASTConsumer() override = default;
};

class LgsCLangFeAction final : public clang::ASTFrontendAction {
public:
    path& filePath;

    explicit LgsCLangFeAction(path& filePath) : filePath(filePath) {}
    unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compilerInstance, StringRef file) override {
        return make_unique<LgsCLangASTConsumer>(filePath);
    }
    ~LgsCLangFeAction() override = default;
};
