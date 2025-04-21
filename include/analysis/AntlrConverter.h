#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LgsAnalyser.h"
#include "LgsEnvFile.h"
#include "LogosParser.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIfStmt.h"

class LgsAppFile;
class LgsLoop;
class LgsAssignment;
using namespace std;

class AntlerConverter : public LgsAnalyser {
public:
    LgsFile* getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath);
    LgsEnvFile* getEnvFile(LogosParser::LogosEnvFileContext* ctx, const path& filePath);
    LgsAppFile* getAppFile(LogosParser::LogosAppFileContext* ctx, const path& filePath);
    LgsMainFile* getMainFile(LogosParser::MainFileContext* ctx, const string& filePath);
    LgsObjectFile* getObjectFile(LogosParser::ObjectFileContext* ctx, const string& filePath);
    LgsFile* getInterfaceFile(LogosParser::InterfaceFileContext* ctx, const path& filePath);
    LgsInterface* getInterface(LogosParser::InterfaceFileContext* ctx, const string& parentName);
    LgsObject* getObject(LogosParser::ObjectBodyContext* ctx, const string& objName);
    LgsField* getField(LogosParser::FieldContext* ctx, size_t position);
    LgsFuncImpl* getFuncImpl(LogosParser::FuncImplementationContext* ctx);
    LgsMethodImpl* getMethodImpl(LogosParser::FuncImplementationContext* ctx, LgsObject* obj);
    LgsStmt* getStmt(LogosParser::StatementContext* ctx);
    LgsAssignment* getAssignment(LogosParser::AssignmentContext* ctx);
    LgsStmtBlock* getStmtBlock(LogosParser::StatementsBlockContext* ctx);
    LgsStmt* getReturnStmt(LogosParser::ReturnStatementContext* ctx);
    LgsVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LgsParam* getParam(LogosParser::ExplicitVarDecContext* ctx);
    LgsVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LgsIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);
    LgsStmt* getPatternMatching(LogosParser::PatternMatchingContext* ctx);
    LgsLoop* getLoopStatement(LogosParser::LoopStatementContext* ctx);
    LgsEnum* getEnum(LogosParser::EnumDeclarationContext* ctx);
    LgsExpr* getExpr(LogosParser::ExprContext* ctx, bool isNullable = false);
    LgsExpr* getCast(LogosParser::ExprContext* ctx);
    LgsUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LgsExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    LgsUnaryExpr* getArray(LogosParser::ArrayContext* ctx);
    LgsVariable* getVariable(const string& varName, const antlr4::ParserRuleContext* ctx) const;
    LgsUnaryExpr* getConst(const string& constName, const antlr4::ParserRuleContext* ctx) const;
    LgsFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx);
    LgsSelection* getSelection(LogosParser::SelectionContext* ctx);
    LgsUnaryExpr* getFirstSelection(LogosParser::SelectionContext* ctx);
    vector<LgsUnaryExpr*> getSelectionInnerExprs(LogosParser::SelectionContext* ctx);
    LgsInstance* getInstance(LogosParser::ConstructorContext* ctx);
    LgsArrayIndex* getArrayIndex(LogosParser::ArrayIndexContext* ctx);
    LgsConstExpr* getConstant(LogosParser::ConstantContext* ctx);
    LgsTypeConst* getTypeConstant(antlr4::tree::TerminalNode* type, const LogosParser::SelectionContext* ctx);
    LgsType* getType(LogosParser::TypeContext* ctx);
    LgsType* getTypeFromText(const string& typeText);
    LgsType* getFuncType(LogosParser::FuncImplementationContext* ctx);
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
