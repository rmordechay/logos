#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "logos/LgsErrHandler.h"
#include "LogosParser.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsBreakStmt.h"

using namespace std;
using namespace filesystem;

class LgsStrConst;
class LgsType;
class LgsTypeConst;
class LgsIterIndex;
class LgsInstance;
class LgsSelection;
class LgsFuncCall;
class LgsVariable;
class LgsUnaryExpr;
class LgsExpr;
class LgsEnum;
class LgsIfStmt;
class LgsParam;
class LgsVarDec;
class LgsStmtBlock;
class LgsStmt;
class LgsField;
class LgsFuncType;
class LgsObject;
class LgsInterface;
class LgsConstExpr;
class LgsObjectFile;
class LgsMainFunc;
class LgsMainFile;
class LgsFile;
class LgsEnvFile;
class LgsAppFile;
class LgsForLoop;
class LgsAssignment;

class AntlerConverter {
public:
    LgsErrHandler errHandler;
    string filePath;

    LgsFile* getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath);
    LgsEnvFile* getEnvFile(LogosParser::LogosEnvFileContext* ctx);
    LgsAppFile* getAppFile(LogosParser::LogosAppFileContext* ctx);
    LgsMainFile* getMainFile(LogosParser::MainFileContext* ctx);
    LgsMainFunc* getMainFunc(LogosParser::FuncImplContext* ctx);
    LgsObjectFile* getObjectFile(LogosParser::ObjectFileContext* ctx);
    LgsFile* getInterfaceFile(LogosParser::InterfaceFileContext* ctx);
    LgsInterface* getInterface(LogosParser::InterfaceBodyContext* ctx, const string& interfaceName);
    LgsObject* getObject(LogosParser::ObjectBodyContext* ctx, const string& objName, bool isSingleton = false);
    void setParams(LgsFuncType* funcType, const vector<LogosParser::ParamContext*>& params);
    bool setMainArgsParam(LgsMainFunc* mainFunc, LogosParser::FuncSignatureContext* funcSignature);
    LgsField* getField(LogosParser::FieldContext* ctx);
    LgsFunc* getFuncImpl(LogosParser::FuncImplContext* ctx);
    LgsFunc* getAnonymousFunc(LogosParser::AnonnymosFuncContext* ctx);
    LgsFunc* getMethodImpl(LogosParser::MethodImplementationContext* ctx, LgsObject* obj);
    LgsStmt* getStmt(LogosParser::StatementContext* ctx);
    LgsAssignment* getAssignment(LogosParser::AssignmentContext* ctx);
    LgsStmtBlock* getStmtBlock(LogosParser::StatementsBlockContext* ctx);
    LgsBreakStmt* getBreakStmt(LogosParser::StatementContext* ctx) const;
    LgsStmt* getReturnStmt(LogosParser::ReturnStatementContext* ctx);
    LgsVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LgsFuncType* getFuncType(LogosParser::FuncTypeContext* ctx);
    LgsVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LgsIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);
    LgsStmt* getPatternMatching(LogosParser::PatternMatchingContext* ctx);
    LgsForLoop* getLoopStatement(LogosParser::LoopStatementContext* ctx);
    LgsForLoop* getRangeLoop(LogosParser::LoopStatementContext* ctx);
    LgsForLoop* getForeachLoop(LogosParser::LoopStatementContext* ctx);
    LgsEnum* getEnum(LogosParser::EnumDeclarationContext* ctx);
    LgsExpr* getExpr(LogosParser::ExprContext* ctx, bool isNullable = false);
    LgsExpr* getCast(LogosParser::ExprContext* ctx);
    LgsUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LgsExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    LgsUnaryExpr* getArrayExpr(LogosParser::ArrayContext* ctx);
    LgsUnaryExpr* getHashMap(LogosParser::HashMapContext* ctx);
    LgsVariable* getVariable(const string& varName, const antlr4::ParserRuleContext* ctx) const;
    LgsUnaryExpr* getConst(const string& constName, const antlr4::ParserRuleContext* ctx) const;
    LgsFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx);
    LgsUnaryExpr* getVector(LogosParser::VectorContext* vector);
    LgsSelection* getSelection(LogosParser::SelectionContext* ctx);
    LgsUnaryExpr* getFirstSelection(LogosParser::SelectionContext* ctx);
    vector<LgsUnaryExpr*> getSelectionInnerExprs(LogosParser::SelectionContext* ctx);
    LgsInstance* getInstance(LogosParser::ConstructorContext* ctx);
    LgsIterIndex* getIterIndex(LogosParser::IterIndexContext* ctx);
    LgsConstExpr* getConstant(LogosParser::ConstantContext* ctx);
    LgsConstExpr* getStrConst(string& value) const;
    LgsTypeConst* getTypeConstant(antlr4::tree::TerminalNode* type, const LogosParser::SelectionContext* ctx);
    LgsType* getType(LogosParser::TypeContext* ctx);
    LgsType* getArrayType(LogosParser::TypeContext* ctx);
    LgsType* getTypeFromText(antlr4::tree::TerminalNode* typeToken) const;
    bool isTypePrimitive(antlr4::tree::TerminalNode* typeToken, const antlr4::ParserRuleContext* ctx) const;
    LgsType* getFuncReturnType(LogosParser::TypeContext* ctx);
    LgsExpr* getExpr(const string& codeText) const;
    void parseTemplateStr(LgsStrConst* strConst) const;
    void cleanStr(string& value) const;
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
