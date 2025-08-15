#pragma once
#include "LogosParser.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsErrHandler.h"
#include "stmts/LgsAssignment.h"


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
class LgsStmtsBlock;
class LgsStmt;
class LgsField;
class LgsFuncType;
class LgsObject;
class LgsInterface;
class LgsObjectFile;
class LgsMainFunc;
class LgsMainFile;
class LgsFile;
class LgsEnvFile;
class LgsAppFile;
class LgsForLoop;
class LgsAssignment;

class AntlrConverter {
public:
    fs::path filePath;
    LgsErrHandler errHandler;
    LgsSymbolTable& globals;
    std::stack<LgsForLoop*> loopStack;

    explicit AntlrConverter(const fs::path& filePath, LgsSymbolTable& globals) : filePath(filePath), globals(globals) {}
    LgsFile* getLogosFile(LogosParser::LogosFileContext* ctx);
    LgsEnvFile* getEnvFile(LogosParser::LogosEnvFileContext* ctx);
    LgsAppFile* getAppFile(LogosParser::LogosAppFileContext* ctx);
    LgsMainFile* getMainFile(LogosParser::MainFileContext* ctx);
    LgsMainFunc* getMainFunc(LogosParser::FuncContext* ctx);
    bool setMainArgsParam(const LgsMainFunc* mainFunc, LogosParser::FuncSignatureContext* funcSignature);
    LgsObjectFile* getObjectFile(LogosParser::ObjectFileContext* ctx);
    LgsFile* getInterfaceFile(LogosParser::InterfaceFileContext* ctx);
    LgsInterface* getInterface(LogosParser::InterfaceBodyContext* ctx, antlr4::tree::TerminalNode* interfaceName);
    LgsObject* getObject(LogosParser::ObjectBodyContext* ctx, antlr4::tree::TerminalNode* objName, bool isSingleton);
    LgsField* getField(LogosParser::FieldContext* ctx, std::string& parentName, size_t position);
    LgsFunc* getFunc(LogosParser::FuncContext* ctx);
    void setParams(LgsFuncType* funcType, const std::vector<LogosParser::ParamContext*>& params);
    LgsFunc* getAnonymousFunc(LogosParser::AnonnymosFuncContext* ctx);
    LgsParam getParam(LgsFuncType* funcType, LogosParser::ParamContext* param);
    LgsField* getInterfaceField(LogosParser::InterfaceFieldContext* ctx, std::string& parentName);
    LgsFunc* getMethod(LogosParser::MethodContext* ctx, LgsType* obj);
    LgsStmt* getDeferStmt(LogosParser::DeferStmtContext* ctx);
    LgsStmt* getStmt(LogosParser::StatementContext* ctx);
    LgsAssignment* getAssignment(LogosParser::AssignmentContext* ctx);
    LgsStmtsBlock* getStmtBlock(LogosParser::StatementsBlockContext* ctx);
    LgsCoroutine* getCoroutine(LogosParser::CoroutineContext* ctx);
    LgsVarDec* getVarDec(antlr4::tree::TerminalNode* name, LgsExpr* expr = nullptr) const;
    LgsVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LgsVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LgsStmt* getReturnStmt(LogosParser::ReturnStatementContext* ctx);
    LgsBreak* getBreakStmt(LogosParser::StatementContext* ctx);
    LgsStmt* getContinueStmt(const LogosParser::StatementContext* ctx);
    LgsIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);
    LgsStmt* getPatternMatching(LogosParser::PatternMatchingContext* ctx);
    LgsForLoop* getForLoop(LogosParser::LoopStatementContext* ctx);
    LgsForLoop* getRangeLoop(LogosParser::LoopStatementContext* ctx);
    LgsForLoop* getForeachLoop(LogosParser::LoopStatementContext* ctx);
    LgsForLoop* getWhileLoop(const LogosParser::LoopStatementContext* ctx);
    LgsForLoop* getInfiniteLoop(LogosParser::LoopStatementContext* ctx) const;
    LgsEnum* getEnum(LogosParser::EnumDeclarationContext* ctx);
    LgsExpr* getExpr(LogosParser::ExprContext* ctx);
    LgsExpr* getCast(LogosParser::ExprContext* ctx);
    LgsUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LgsExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    LgsUnaryExpr* getPrefixExpr(LogosParser::PrefixExprContext* ctx);
    LgsPostfixExpr* getPostfixExpr(LogosParser::PostfixExprContext* ctx);
    LgsUnaryExpr* getArrayExpr(LogosParser::ArrayExprContext* ctx);
    LgsUnaryExpr* getHashMap(LogosParser::HashMapContext* ctx);
    LgsVariable* getVariable(antlr4::tree::TerminalNode* ctx) const;
    LgsFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx);
    LgsUnaryExpr* getVector(LogosParser::VectorContext* vector);
    LgsSelection* getSelection(LogosParser::SelectionContext* ctx);
    LgsUnaryExpr* getFirstSelection(LogosParser::SelectionContext* ctx);
    std::vector<LgsUnaryExpr*> getSelectionExprs(LogosParser::SelectionContext* ctx);
    LgsInstance* getInstance(LogosParser::InstanceContext* ctx);
    LgsIterIndex* getIterIndex(LogosParser::IterIndexContext* ctx);
    LgsUnaryExpr* getConstant(LogosParser::ConstantContext* ctx);
    LgsStrConst* getStrConst(antlr4::tree::TerminalNode* ctx);
    LgsUnaryExpr* getNullValue(const antlr4::tree::TerminalNode* ctx) const;
    LgsUnaryExpr* getLoopIsFirst(LogosParser::IsFirstContext* ctx);
    LgsUnaryExpr* getLoopIsLast(LogosParser::IsLastContext* ctx);
    LgsType* getType(LogosParser::TypeContext* ctx);
    LgsGroup* getGroup(LogosParser::GroupContext* ctx);
    LgsFuncType* getFuncType(LogosParser::FuncTypeContext* ctx);
    LgsType* getArrayType(LogosParser::TypeContext* ctx);
    LgsType* getTypeFromText(antlr4::tree::TerminalNode* typeToken) const;
    LgsType* getFuncReturnType(LogosParser::TypeContext* ctx);
    void addFileSymbol(LgsMainFile* file, const LgsSymbol& newSymbol);
    bool isArgsDuplicate(const std::unordered_set<std::string>& initializedArgs, LgsVarDec* varDec);
    bool validateTypeName(const std::string& typeName, LgsLocation* location);
    void setLocation(LgsLocation& location, const antlr4::Token* start) const;
    void extractStrParts(LgsStrConst& strConst);
    ~AntlrConverter() = default;
};
