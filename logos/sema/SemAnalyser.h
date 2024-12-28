#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "CodeNode.h"
#include "LogosPackage.h"
#include "LogosParser.h"
#include "Scope.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosUnaryExpr.h"

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
    LogosExpr getExpr(LogosParser::ExprContext* ctx) const;
    LogosUnaryExpr getUnaryExpr(LogosParser::UnaryExprContext* ctx) const;
    LogosBinaryExpr getBinaryExpr(LogosParser::BinaryExprContext* ctx) const;
    void printError(int errorCode);
    ~SemAnalyser();
};


#endif //SEMANTICANALYSER_H
