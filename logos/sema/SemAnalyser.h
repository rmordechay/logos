#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "CodeNode.h"
#include "LogosPackage.h"
#include "LogosParser.h"
#include "Scope.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosUnaryExpr.h"

using namespace std;

class SemAnalyser {
public:
    LogosPackage* rootPackage;
    Scope* rootScope;
    Scope* currentScope;
    LogosFile* mainFile;
    std::vector<CodeNode*> codeNodes;

    explicit SemAnalyser(LogosPackage* rootPackage);
    void analyseProject();
    void visitPackage(const LogosPackage* package);
    void visitLogosFile(LogosParser::LogosFileContext* ctx);
    void visitImportStatement(LogosParser::ImportStatementContext* ctx) const;
    void visitMainFile();
    void visitFuncImplementation(LogosParser::FuncImplementationContext* ctx);
    void visitObjectFile(LogosParser::ObjectFileContext* ctx);
    void visitObjectImplements(LogosParser::ObjectImplementsContext* ctx);
    void visitStatement(LogosParser::StatementContext* ctx);
    void visitExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx) const;
    void visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    void visitExpr(LogosParser::ExprContext* ctx);
    void visitUnaryExpr(LogosParser::UnaryExprContext* ctx);
    void visitBuiltinFunc(LogosParser::FuncCallContext* ctx, const std::string& funcName);
    void visitFuncCall(LogosParser::FuncCallContext* ctx);
    shared_ptr<LogosExpr> getExpr(LogosParser::ExprContext* ctx) const;
    shared_ptr<LogosTypedValue> getUnaryTypedValue(LogosParser::UnaryExprContext* ctx) const;
    shared_ptr<LogosExpr> getBinaryExpr(LogosParser::BinaryExprContext* ctx) const;
    shared_ptr<LogosExpr> getBoolExpr(LogosParser::BoolExprContext* ctx) const;
    void printError(int errorCode) const;
    ~SemAnalyser();
};


#endif //SEMANTICANALYSER_H
