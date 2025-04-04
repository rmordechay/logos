#include "LgsC.h"

#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include <clang/Tooling/CompilationDatabase.h>

using namespace clang;
using namespace std;

class MyVisitor : public RecursiveASTVisitor<MyVisitor> {
public:
    ASTContext* context;

    explicit MyVisitor(ASTContext* context) : context(context) {}

    bool VisitFunctionDecl(const FunctionDecl* decl) const {
        outs() << "Function: " << decl->getNameAsString() << "\n";
        return true;
    }

    bool VisitTypedefDecl(const TypedefDecl *typedefDec) const {
        outs() << "Typedef: " << typedefDec->getNameAsString() << "\n";
        const auto qt = typedefDec->getUnderlyingType();

        if (const auto recordType = qt->getAs<RecordType>()) {
            const auto recordDecl = recordType->getDecl();
            if (recordDecl->isCompleteDefinition()) {
                for (const auto *field : recordDecl->fields()) {
                    auto fieldType = field->getType();
                    auto fieldName = field->getNameAsString();
                    auto fieldTypeName = fieldType.getAsString();
                    outs() << "  Field: " << fieldName << " of type: " << fieldTypeName << "\n";
                }
            }
        }
        return true;
    }
};

class MyConsumer final : public ASTConsumer {
public:
    MyVisitor visitor;

    explicit MyConsumer(ASTContext* context) : visitor(context) {}
    void HandleTranslationUnit(ASTContext& ctx) override {
        visitor.TraverseDecl(ctx.getTranslationUnitDecl());
    }
};

class FunctionFrontendAction final : public ASTFrontendAction {
public:
    std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& CI, StringRef) override {
        return std::make_unique<MyConsumer>(&CI.getASTContext());
    }
};

void LgsC::l() const {
    const vector<std::string> args = {"-std=c11", "-I/usr/include", "-I."};
    const FixedCompilationDatabase db(".", args);
    ClangTool tool(db, {"../test.h"});
    tool.run(newFrontendActionFactory<FunctionFrontendAction>().get());
}
