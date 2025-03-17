#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LogosParser.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIf.h"
#include "types/LgsInt.h"
#include "exprs/unary/constants/LgsTypeConst.h"

class LgsAssignment;
using namespace std;

class AntlerConverter {
public:
    static LgsFile* getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath);
    static LgsMainFile* getMainFile(LogosParser::MainFileContext* ctx, const string& filePath);
    static LgsObjectFile* getObjectFile(LogosParser::ObjectFileContext* ctx, const string& filePath);
    static LgsObject* getObject(LogosParser::ObjectFileContext* ctx);
    static LgsField* getField(LogosParser::ExplicitVarDecContext* varDec, size_t position, const string& parentName);
    static LgsFuncImpl* getFuncImpl(LogosParser::FuncImplementationContext* ctx);
    static LgsMethodImpl* getMethodImpl(LogosParser::FuncImplementationContext* ctx, const LgsObject* obj);
    static LgsStmt* getStmt(LogosParser::StatementContext* ctx);
    static LgsAssignment* getAssignment(LogosParser::AssignmentContext* ctx);
    static LgsStmtBlock* getStmtBlock(LogosParser::StatementsBlockContext* ctx);
    static LgsVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    static LgsParam* getParam(LogosParser::ExplicitVarDecContext* ctx);
    static LgsVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    static LgsIf* getIfStatement(LogosParser::IfStatementContext* ctx);
    static LgsLoop* getLoopStatement(LogosParser::LoopStatementContext* ctx);
    static LgsExpr* getExpr(LogosParser::ExprContext* ctx);
    static LgsUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    static LgsExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    static LgsUnaryExpr* getArray(LogosParser::ArrayContext* ctx);
    static LgsVariable* getVariable(const string& varName, const ParserRuleContext* ctx);
    static LgsFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx);
    static LgsUnaryExpr* getFirstSelection(LogosParser::SelectionContext* ctx);
    static vector<LgsUnaryExpr*> getSelectionInnerExprs(LogosParser::SelectionContext* ctx);
    static LgsSelection* getSelection(LogosParser::SelectionContext* ctx);
    static LgsInstance* getInstance(LogosParser::ConstructorContext* ctx);
    static LgsArrayIndex* getArrayIndex(LogosParser::ArrayIndexContext* ctx);
    static LgsConst* getConstant(LogosParser::ConstantContext* ctx);
    static LgsTypeConst* getTypeConstant(tree::TerminalNode* type, const LogosParser::SelectionContext* ctx);
    static LgsType* getType(LogosParser::TypeContext* type);
    static LgsType* getFuncType(LogosParser::FuncImplementationContext* ctx);
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
