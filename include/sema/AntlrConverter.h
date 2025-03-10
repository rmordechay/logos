#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LogosParser.h"
#include "exprs/LogosMethodCall.h"
#include "exprs/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "stmts/LogosAssignment.h"
#include "stmts/LogosIf.h"
#include "types/LogosInt.h"

class LogosAssignment;
using namespace std;

class AntlerConverter {
public:
    const string& filePath;

    explicit AntlerConverter(const string& filePath) : filePath(filePath) {}
    LogosFile* getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath);
    LogosMainFile* getMainFile(LogosParser::MainFileContext* ctx);
    LogosObjectFile* getObjectFile(LogosParser::ObjectFileContext* ctx);
    static LogosObject* getObject(LogosParser::ObjectFileContext* ctx);
    static LogosField* getField(LogosParser::ExplicitVarDecContext* varDec, const string& parentName, size_t position);
    static LogosFuncImpl* getFunc(LogosParser::FuncImplementationContext* ctx);
    static LogosMethodImpl* getMethod(LogosParser::FuncImplementationContext* ctx, LogosObject* obj);
    static LogosStmt* getStmt(LogosParser::StatementContext* ctx);
    static LogosAssignment* getAssignment(LogosParser::AssignmentContext* ctx);
    static LogosStmtBlock* getStmtBlock(LogosParser::StatementsBlockContext* ctx);
    static LogosVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    static LogosParam* getParam(LogosParser::ExplicitVarDecContext* ctx);
    static LogosVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    static LogosIf* getIfStatement(LogosParser::IfStatementContext* ctx);
    static LogosLoop* getLoopStatement(LogosParser::LoopStatementContext* ctx);
    static LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    static LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    static LogosExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    static LogosUnaryExpr* getArray(LogosParser::ArrayContext* ctx);
    static LogosVariable* getVariable(const string& varName, const ParserRuleContext* ctx);
    static LogosFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx);
    static LogosMethodCall *getMethodCall(LogosParser::FuncCallContext* ctx);
    static LogosUnaryExpr* getFirstSelection(const LogosParser::SelectionContext* ctx, LogosParser::FirstSelectionElementContext* firstExpr);
    static vector<LogosUnaryExpr*> getInnerSelections(const vector<LogosParser::InnerSelectionElementContext*>& ctx);
    static LogosSelection* getSelection(LogosParser::SelectionContext* ctx);
    static LogosInstance* getInstance(LogosParser::ConstructorContext* ctx);
    static LogosArrayIndex* getArrayIndex(LogosParser::ArrayIndexContext* ctx);
    static LogosUnaryExpr* getConstant(LogosParser::ConstantContext* ctx);
    static LogosType* getType(tree::TerminalNode* type);
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
