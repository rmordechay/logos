#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LogosParser.h"
#include "funcs/LogosUserFunc.h"
#include "exprs/LogosUnaryExpr.h"

#include "exprs/LogosFuncCall.h"
#include "exprs/LogosVariable.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "stmts/LogosFieldDef.h"
#include "stmts/LogosIf.h"
#include "types/LogosInt.h"

#include <stmts/LogosLoop.h>

#include "exprs/LogosArrayIndex.h"

class LogosFieldDefinition;
using namespace std;

class AntlerConverter {
public:
    const string& filePath;
    explicit AntlerConverter(const string& filePath) : filePath(filePath) {}
    LogosFile* getLogosFile(LogosParser::LogosFileContext* ctx, const filesystem::path& filePath);
    LogosMainFile* getMainFile(LogosParser::MainFileContext* ctx);
    LogosObjectFile* getObjFile(LogosParser::ObjectFileContext* ctx);
    LogosObject* getObject(LogosParser::ObjectFileContext* ctx);
    LogosField *getField(LogosParser::ExplicitVarDecContext* varDec, const string& parentName, size_t position);
    LogosUserFunc* getFunc(LogosParser::FuncImplementationContext* ctx);
    LogosStmt* getStmt(LogosParser::StatementContext* ctx);
    LogosFieldDefinition* getFieldDef(LogosParser::FieldDefContext* ctx);
    LogosStmtBlock* getStmtBlock(LogosParser::StatementsBlockContext* ctx);
    LogosVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LogosVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LogosIf* getIfStatement(LogosParser::IfStatementContext* ctx);
    LogosLoop* getLoopStatement(LogosParser::LoopStatementContext* ctx);
    LogosSelection* getSelection(LogosParser::SelectionContext* selection);
    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    LogosExpr* getArray(LogosParser::ArrayContext* array);
    LogosFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx);
    LogosUnaryExpr* getSelectionElementExpr(LogosParser::SelectionElementContext* ctx);
    LogosInstance* getInstance(LogosParser::ConstructorContext* ctx);
    LogosArrayIndex* getArrayIndex(LogosParser::ArrayIndexContext* ctx);
    static LogosUnaryExpr* getConstant(LogosParser::ConstantContext* ctx);
    static LogosType* getType(antlr4::tree::TerminalNode* type);
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
