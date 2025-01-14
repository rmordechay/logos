#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "CodeNode.h"
#include "LogosDefinitions.h"
#include "LogosPackage.h"
#include "LogosParser.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"
#include "funcs/LogosPrint.h"
#include "types/LogosInt.h"

#include <exprs/LogosVariableExpr.h>

using namespace std;

class SemAnalyser {
public:
    map<string, LogosSymbol*> rootScope;
    map<string, LogosSymbol*> currentScope = {
        {LOGOS_PRINT.name, new LogosSymbol(LOGOS_PRINT.type, LOGOS_PRINT)}
    };
    vector<CodeNode*> codeNodes;

    void analyseProject(const LogosFile* mainFile);
    void visitMainFile(const LogosFile* mainFile);
    void visitFuncImplementation(LogosParser::FuncImplementationContext* ctx);
    void visitStatement(LogosParser::StatementContext* ctx);
    void visitExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    void visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    void visitFuncCall(LogosParser::FuncCallContext* ctx);
    void visitIfStatement(LogosParser::IfStatementContext* ctx);
    void addSymbol(const string& variableName, LogosExpr* logosExpr);

    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosUnaryExpr* getConstantExpr(LogosParser::ConstantContext* ctx) const;
    LogosUnaryExpr* getFuncCallExpr(LogosParser::FuncCallContext* ctx);
    LogosUnaryExpr* getVariableExpr(const string& symbolName);
    LogosSymbol* resolveSymbol(const string& symbolName);
    ~SemAnalyser();
};


#endif //SEMANTICANALYSER_H
