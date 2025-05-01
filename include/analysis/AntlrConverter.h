#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LgsEnvFile.h"
#include "LgsErrorHandler.h"
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
using namespace filesystem;

class AntlerConverter {
public:
    LgsFuncImpl* currentFunc = nullptr;
    LgsMethodImpl* currentMethod = nullptr;
    LgsErrorHandler errHandler;

    LgsFile* getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath);
    LgsEnvFile* getEnvFile(LogosParser::LogosEnvFileContext* ctx, const path& filePath);
    LgsAppFile* getAppFile(LogosParser::LogosAppFileContext* ctx, const path& filePath);
    LgsMainFile* getMainFile(LogosParser::MainFileContext* ctx, const string& filePath);
    LgsObjectFile* getObjectFile(LogosParser::ObjectFileContext* ctx, const string& filePath);
    LgsFile* getInterfaceFile(LogosParser::InterfaceFileContext* ctx, const path& filePath);
    LgsInterface* getInterface(LogosParser::InterfaceBodyContext* ctx, const string& interfaceName, const string& filePath);
    LgsObject* getObject(LogosParser::ObjectBodyContext* ctx, const string& objName, const string& filePath, bool isSingleton = false);
    void setParams(LogosParser::FuncSignatureContext* funcSignature, LgsFuncSignature* signature);
    LgsField* getField(LogosParser::FieldContext* ctx);
    LgsFuncImpl* getFuncImpl(LogosParser::FuncImplementationContext* ctx);
    LgsMethodImpl* getMethodImpl(LogosParser::MethodImplementationContext* ctx, LgsObject* obj);
    LgsStmt* getStmt(LogosParser::StatementContext* ctx);
    LgsAssignment* getAssignment(LogosParser::AssignmentContext* ctx);
    LgsStmtBlock* getStmtBlock(LogosParser::StatementsBlockContext* ctx);
    LgsStmt* getReturnStmt(LogosParser::ReturnStatementContext* ctx);
    LgsVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LgsParam* getParam(LogosParser::ExplicitVarDecContext* ctx);
    LgsParam* getParamFunc(LogosParser::FuncSignatureContext* ctx);
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
    LgsFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx, bool isMethodCall = false);
    LgsUnaryExpr* getVector(LogosParser::VectorContext* vector);
    LgsSelection* getSelection(LogosParser::SelectionContext* ctx);
    LgsUnaryExpr* getFirstSelection(LogosParser::SelectionContext* ctx);
    vector<LgsUnaryExpr*> getSelectionInnerExprs(LogosParser::SelectionContext* ctx);
    LgsInstance* getInstance(LogosParser::ConstructorContext* ctx);
    LgsArrayIndex* getArrayIndex(LogosParser::ArrayIndexContext* ctx);
    LgsConstExpr* getConstant(LogosParser::ConstantContext* ctx) const;
    LgsTypeConst* getTypeConstant(antlr4::tree::TerminalNode* type, const LogosParser::SelectionContext* ctx) const;
    LgsType* getType(LogosParser::TypeContext* ctx) const;
    LgsType* getArrayType(LogosParser::TypeContext* ctx, LgsType* underlyingType) const;
    LgsType* getTypeFromText(const string& typeText, const antlr4::ParserRuleContext* ctx) const;
    LgsType* getFuncType(LogosParser::FuncSignatureContext* ctx) const;
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
