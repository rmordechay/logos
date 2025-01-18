#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LogosPackage.h"
#include "LogosParser.h"
#include "LogosSymbol.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"

using namespace std;

class SemAnalyser {
public:
    vector<CodeGeneration*> codeNodes;
    stack<map<string, LogosSymbol*>> stack;

    void analyseProject(const LogosFile* mainFile);
    void visitMainFile(const LogosFile* mainFile);
    void visitFuncImplementation(LogosParser::FuncImplementationContext* ctx);
    void visitStatement(LogosParser::StatementContext* ctx);
    void visitImplicitVarDec(LogosParser::VariableDefintionContext* ctx);
    void visitFuncCall(LogosParser::FuncCallContext* ctx);
    void visitStatementList(const std::vector<LogosParser::StatementContext*>& statements);
    void visitIfStatement(LogosParser::IfStatementContext* ctx);

    const LogosType& getType(const string& typeText);
    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosUnaryExpr* getVariableExpr(const string& symbolName);
    LogosUnaryExpr* getFuncCallExpr(LogosParser::FuncCallContext* ctx);
    static LogosUnaryExpr* getConstantExpr(LogosParser::ConstantContext* ctx);

    void addSymbol(const string& variableName, LogosExpr* logosExpr);
    LogosSymbol* resolveSymbol(const string& symbolName);
    ~SemAnalyser();
};


#endif //SEMANTICANALYSER_H
