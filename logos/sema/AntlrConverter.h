#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H
#include "LogosParser.h"

#include "LogosDefinitions.h"
#include "LogosParser.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosConstructorExpr.h"
#include "exprs/LogosFuncCallExpr.h"
#include "exprs/LogosOperator.h"
#include "exprs/LogosVariableExpr.h"
#include "files/LogosMainFile.h"
#include "funcs/LogosPrint.h"
#include "funcs/LogosUserFunc.h"
#include "stmts/LogosIfStmt.h"
#include "stmts/LogosReturnStmt.h"
#include "stmts/LogosVarDec.h"
#include <vector>

class AntlerConverter {
public:
    LogosFile* getMainFile(LogosParser::MainFileContext* ctx);
    LogosFunc* getFunc(LogosParser::FuncImplementationContext* ctx);
    LogosStmt* getStmt(LogosParser::StatementContext* ctx);
    vector<LogosStmt*> getStmtList(LogosParser::StatementsBlockContext* ctx);
    LogosVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LogosVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LogosIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);

    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosConstructorExpr* getConstructorCallExpr(LogosParser::ConstructorCallContext* ctx);
    LogosFuncCallExpr* getFuncCallExpr(LogosParser::FuncCallContext* ctx);
    static LogosUnaryExpr* getConstantExpr(LogosParser::ConstantContext* ctx);
    static const LogosType* getType(const string& typeText);

    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
