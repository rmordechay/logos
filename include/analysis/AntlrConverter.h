#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

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

class AntlerConverter {
public:
    static LgsFile* getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath);
    static LgsEnvFile* getEnvFile(LogosParser::LogosEnvFileContext* ctx, const path& filePath);
    static LgsAppFile* getAppFile(LogosParser::LogosAppFileContext* ctx, const path& filePath);
    static LgsMainFile* getMainFile(LogosParser::MainFileContext* ctx, const string& filePath);
    static LgsObjectFile* getObjectFile(LogosParser::ObjectFileContext* ctx, const string& filePath);
    static LgsFile* getInterfaceFile(LogosParser::InterfaceFileContext* ctx, const path& filePath);
    static LgsInterface* getInterface(LogosParser::InterfaceFileContext* ctx, const string& parentName);
    static LgsObject* getObject(LogosParser::ObjectBodyContext* ctx, const string& objName);
    static LgsField* getField(LogosParser::ExplicitVarDecContext* ctx, size_t position, const string& parentName);
    static LgsFuncImpl* getFuncImpl(LogosParser::FuncImplementationContext* ctx);
    static LgsMethodImpl* getMethodImpl(LogosParser::FuncImplementationContext* ctx, LgsObject* obj);
    static LgsStmt* getStmt(LogosParser::StatementContext* ctx);
    static LgsAssignment* getAssignment(LogosParser::AssignmentContext* ctx);
    static LgsStmtBlock* getStmtBlock(LogosParser::StatementsBlockContext* ctx);
    static LgsVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    static LgsParam* getParam(LogosParser::ExplicitVarDecContext* ctx);
    static LgsVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    static LgsIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);
    static LgsStmt* getPatternMatching(LogosParser::PatternMatchingContext* ctx);
    static LgsLoop* getLoopStatement(LogosParser::LoopStatementContext* ctx);
    static LgsEnum* getEnum(LogosParser::EnumDeclarationContext* ctx);
    static LgsExpr* getExpr(LogosParser::ExprContext* ctx, bool isNullable = false);
    static LgsExpr* getCast(LogosParser::ExprContext* ctx);
    static LgsUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    static LgsExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    static LgsUnaryExpr* getArray(LogosParser::ArrayContext* ctx);
    static LgsVariable* getVariable(const string& varName, const antlr4::ParserRuleContext* ctx);
    static LgsUnaryExpr* getConst(const string& constName, const antlr4::ParserRuleContext* ctx);
    static LgsFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx);
    static LgsSelection* getSelection(LogosParser::SelectionContext* ctx);
    static LgsUnaryExpr* getFirstSelection(LogosParser::SelectionContext* ctx);
    static vector<LgsUnaryExpr*> getSelectionInnerExprs(LogosParser::SelectionContext* ctx);
    static LgsInstance* getInstance(LogosParser::ConstructorContext* ctx);
    static LgsArrayIndex* getArrayIndex(LogosParser::ArrayIndexContext* ctx);
    static LgsConstExpr* getConstant(LogosParser::ConstantContext* ctx);
    static LgsTypeConst* getTypeConstant(antlr4::tree::TerminalNode* type, const LogosParser::SelectionContext* ctx);
    static LgsType* getType(LogosParser::TypeContext* ctx);
    static LgsType* getTypeFromText(const string& typeText);
    static LgsType* getFuncType(LogosParser::FuncImplementationContext* ctx);
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
