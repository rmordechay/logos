#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "CodeNode.h"
#include "LogosPackage.h"
#include "LogosParser.h"
#include "Scope.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"

using namespace std;

class SemAnalyser {
public:
    const LogosPackage& rootPackage;
    Scope* rootScope;
    Scope* currentScope;
    LogosFile* mainFile;
    std::vector<CodeNode*> codeNodes;

    explicit SemAnalyser(const LogosPackage& rootPackage);
    void analyseProject();
    void visitMainFile();
    void visitFuncImplementation(LogosParser::FuncImplementationContext* ctx);
    void visitStatement(LogosParser::StatementContext* ctx);
    void visitExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    void addSymbol(const std::string& variableName, LogosExpr* logosExpr) const;
    void visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    void visitFuncCall(LogosParser::FuncCallContext* ctx);
    void printError(int errorCode) const;

    LogosExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosConstantExpr* getConstantExpr(LogosParser::ConstantContext* ctx) const;
    LogosFuncCallExpr* getFuncCallExpr(LogosParser::FuncCallContext* ctx);

    ~SemAnalyser();
};


#endif //SEMANTICANALYSER_H
