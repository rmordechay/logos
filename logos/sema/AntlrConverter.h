#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LogosRootPackage.h"
#include "LogosPackage.h"
#include "LogosParser.h"
#include "LogosSymbol.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"
#include "files/LogosMainFile.h"
#include "stmts/LogosIfStmt.h"

using namespace std;

class AntlerConverter {
public:
    LogosMainFile* getMainFile(LogosParser::MainFileContext* ctx);
    LogosFunc* getFunc(LogosParser::FuncImplementationContext* ctx);
    LogosStmt* getStmt(LogosParser::StatementContext* ctx);
    vector<LogosStmt*> getStmtList(LogosParser::StatementsBlockContext* ctx);
    LogosVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LogosVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LogosIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);

    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosFuncCallExpr* getFuncCallExpr(LogosParser::FuncCallContext* ctx);
    static LogosUnaryExpr* getConstantExpr(LogosParser::ConstantContext* ctx);
    static const LogosType* getType(const string& typeText);

    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
