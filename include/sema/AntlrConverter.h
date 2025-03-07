#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LogosParser.h"
#include "exprs/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "funcs/LogosParam.h"
#include "stmts/LogosAssignment.h"
#include "stmts/LogosIf.h"
#include "types/LogosInt.h"
#include <funcs/LogosMethodImpl.h>


class LogosAssignment;
using namespace std;

class AntlerConverter {
public:
    const string& filePath;
    explicit AntlerConverter(const string& filePath) : filePath(filePath) {}
    LogosFile* getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath);
    LogosMainFile* getMainFile(LogosParser::MainFileContext* ctx);
    LogosObjectFile* getObjFile(LogosParser::ObjectFileContext* ctx);
    LogosObject* getObject(LogosParser::ObjectFileContext* ctx);
    LogosField *getField(LogosParser::ExplicitVarDecContext* varDec, const string& parentName, size_t position);
    LogosFuncImpl* getFunc(LogosParser::FuncImplementationContext* ctx);
    LogosMethodImpl* getMethod(LogosParser::FuncImplementationContext* ctx, LogosObject* obj);
    LogosStmt* getStmt(LogosParser::StatementContext* ctx);
    LogosAssignment* getAssignment(LogosParser::AssignmentContext* ctx);
    LogosStmtBlock* getStmtBlock(LogosParser::StatementsBlockContext* ctx);
    LogosVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LogosParam* getParam(LogosParser::ExplicitVarDecContext* ctx);
    LogosVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LogosIf* getIfStatement(LogosParser::IfStatementContext* ctx);
    LogosLoop* getLoopStatement(LogosParser::LoopStatementContext* ctx);
    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    LogosUnaryExpr* getArray(LogosParser::ArrayContext* ctx);
    LogosVariable* getVariable(const string& varName, const ParserRuleContext* ctx) const;
    LogosFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx);
    LogosSelection* getSelection(LogosParser::SelectionContext* selection);
    LogosUnaryExpr* getSelectionElementExpr(LogosParser::SelectionElementContext* ctx);
    LogosInstance* getInstance(LogosParser::ConstructorContext* ctx);
    LogosArrayIndex* getArrayIndex(LogosParser::ArrayIndexContext* ctx);
    static LogosUnaryExpr* getConstant(LogosParser::ConstantContext* ctx);
    static LogosType* getType(tree::TerminalNode* type);
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
