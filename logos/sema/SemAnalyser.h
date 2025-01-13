#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LogosPackage.h"
#include "LogosParser.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"

using namespace std;

class SemAnalyser {
public:
    const LogosPackage& rootPackage;
    map<string, LogosSymbol*> rootScope;
    map<string, LogosSymbol*> currentScope;

    explicit SemAnalyser(const LogosPackage& rootPackage);
    void analyseProject();
    void visitMainFile();
    void visitFuncImplementation(LogosParser::FuncImplementationContext* ctx);
    void visitStatement(LogosParser::StatementContext* ctx);
    void visitExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    void visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    void visitFuncCall(LogosParser::FuncCallContext* ctx);
    void addSymbol(const string& variableName, LogosExpr* logosExpr);

    LogosExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosConstantExpr* getConstantExpr(LogosParser::ConstantContext* ctx) const;
    LogosFuncCallExpr* getFuncCallExpr(LogosParser::FuncCallContext* ctx);
    LogosSymbol* resolveSymbol(const string& symbolName);

    ~SemAnalyser();
};


#endif //SEMANTICANALYSER_H
