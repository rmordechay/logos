#pragma once
#include <exprs/LgsJson.h>
#include <types/LgsSubType.h>

#include "LogosParser.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsErrHandler.h"
#include "stmts/LgsAssignment.h"

class LgsNullableExpr;
struct LgsSymbol;
struct LgsAppConfigs;
struct LgsSymbolTable;
class LgsIOPair;
struct LgsPaths;
class LgsStrConst;
class LgsType;
class LgsTypeConst;
class LgsIterIndex;
class LgsInstance;
class LgsSelection;
class LgsFuncCall;
class LgsVariable;
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

class LgsParserAdapter {
public:
    size_t fileID;
    LgsPaths& paths;
    LgsSymbolTable& globals;
    LgsAppConfigs& appConfigs;
    LgsErrHandler errHandler;
    LgsFunc* currentFunc = nullptr;

    explicit LgsParserAdapter(const int fileID, LgsAppConfigs& appConfigs, LgsPaths& paths, LgsSymbolTable& globals) : fileID(fileID), paths(paths), globals(globals), appConfigs(appConfigs) {}
    LgsFile* parseFile(const std::string& codeText, const fs::path& filePath);
    LgsFile* getLogosFile(LogosParser::LogosFileContext* ctx, const fs::path& filePath);
    LgsMainFile* getMainFile(LogosParser::MainFileContext* ctx, const fs::path& filePath);
    LgsObjectFile* getObjectFile(LogosParser::ObjectFileContext* ctx, const fs::path& filePath);
    LgsFile* getInterfaceFile(LogosParser::InterfaceFileContext* ctx, const fs::path& filePath);
    LgsFile* getTestFile(LogosParser::TestFileContext* ctx, const fs::path& filePath);
    LgsEnvFile* getEnvFile(const fs::path& filePath);
    void setAppConfigs();
    LgsObject* getObject(LogosParser::ObjectBodyContext* ctx, antlr4::tree::TerminalNode* objName, bool isSingleton);
    LgsInterface* getInterface(LogosParser::InterfaceBodyContext* ctx, antlr4::tree::TerminalNode* interfaceName);
    LgsSubType* getSubtype(LogosParser::SubtypeContext* ctx);
    LgsFunc* getFunc(LogosParser::FuncContext* ctx);
    LgsMainFunc* getMainFunc(LogosParser::FuncContext* ctx);
    LgsFunc* getLambda(LogosParser::LambdaContext* ctx);
    LgsFunc* getMethod(LogosParser::MethodContext* ctx, LgsType* obj);
    LgsField* getField(LogosParser::FieldContext* ctx, size_t position);
    LgsParam getParam(LgsFuncType* funcType, LogosParser::ParamContext* ctx);
    LgsIOPair* getIOPair(const LogosParser::IoPairContext* ctx) const;
    LgsStmt* getDeferStmt(LogosParser::DeferStmtContext* ctx);
    LgsStmt* getStmt(LogosParser::StatementContext* ctx);
    LgsAssignment* getAssignment(LogosParser::AssignmentContext* ctx);
    LgsStmtsBlock* getStmtBlock(LogosParser::StatementsBlockContext* ctx);
    LgsCoroutine* getCoroutine(LogosParser::CoroutineContext* ctx);
    LgsVarDec* getVarDec(antlr4::tree::TerminalNode* name, bool isConst = false, LgsExpr* expr = nullptr) const;
    LgsVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LgsVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LgsStmt* getReturnStmt(LogosParser::ReturnStatementContext* ctx);
    LgsBreak* getBreakStmt(LogosParser::BreakStmtContext* ctx) const;
    LgsStmt* getIOStmt(LogosParser::IoStatementContext* ctx);
    LgsStmt* getContinueStmt(const LogosParser::StatementContext* ctx) const;
    LgsIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);
    LgsStmt* getPatternMatching(LogosParser::PatternMatchingContext* ctx);
    LgsForLoop* getForLoop(LogosParser::LoopStatementContext* ctx);
    LgsForLoop* getRangeLoop(LogosParser::RangeLoopContext* ctx);
    LgsForLoop* getForeachLoop(LogosParser::LoopStatementContext* ctx);
    LgsForLoop* getWhileLoop(const LogosParser::LoopStatementContext* ctx);
    LgsForLoop* getInfiniteLoop(const LogosParser::LoopStatementContext* ctx) const;
    LgsEnum* getEnum(LogosParser::EnumDeclarationContext* ctx);
    LgsExpr* getExpr(LogosParser::ExprContext* ctx);
    LgsExpr* getCast(LogosParser::ExprContext* ctx);
    LgsExpr* getJSON(LogosParser::JsonContext* ctx);
    LgsExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LgsExpr* getBinaryExpr(LogosParser::ExprContext* ctx);
    LgsExpr* getPrefixExpr(LogosParser::PrefixExprContext* ctx);
    LgsPostfixExpr* getPostfixExpr(LogosParser::PostfixExprContext* ctx);
    LgsArrayExpr* getArrayExpr(LogosParser::ArrayExprContext* ctx);
    LgsExpr* getHashMap(LogosParser::HashMapContext* ctx);
    LgsVariable* getVariable(antlr4::tree::TerminalNode* ctx) const;
    LgsFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx);
    LgsExpr* getVectorExpr(LogosParser::VectorContext* ctx);
    LgsSelection* getSelection(LogosParser::SelectionContext* ctx);
    LgsExpr* getFirstSelection(LogosParser::SelectionContext* ctx);
    std::vector<LgsExpr*> getSelectionExprs(LogosParser::SelectionContext* ctx);
    LgsInstance* getInstance(LogosParser::InstanceContext* ctx);
    LgsIterIndex* getIterIndex(LogosParser::IterIndexContext* ctx);
    LgsExpr* getConstant(LogosParser::ConstantContext* ctx);
    LgsStrConst* getStrConst(antlr4::tree::TerminalNode* ctx);
    LgsNullableExpr* getNullValue(const antlr4::tree::TerminalNode* ctx) const;
    LgsExpr* getLoopMetaVar(antlr4::tree::TerminalNode* ctx) const;
    LgsInstance* getObjectFromJson(LogosParser::JsonObjContext* ctx);
    LgsArrayExpr* getArrayExprFromJson(LogosParser::JsonArrayContext* ctx);
    LgsType* getType(LogosParser::TypeContext* ctx);
    LgsGroup* getGroup(LogosParser::GroupContext* ctx);
    LgsFuncType* getFuncType(LogosParser::FuncTypeContext* ctx);
    LgsType* getArrayType(LogosParser::TypeContext* ctx);
    LgsType* getTypeFromText(antlr4::tree::TerminalNode* ctx) const;
    void setParams(LgsFuncType* funcType, const std::vector<LogosParser::ParamContext*>& params);
    bool setMainArgsParam(const LgsMainFunc* mainFunc, LogosParser::FuncSignatureContext* funcSignature);
    void addFileSymbol(LgsMainFile* file, const LgsSymbol& newSymbol);
    bool isArgsDuplicate(const std::unordered_set<std::string>& initializedArgs, LgsVarDec* varDec);
    bool validateTypeName(const std::string& typeName, const LgsLocation* location);
    void extractStrParts(LgsStrConst& strConst);
    bool checkParserErrors(LogosParser* parser);
    void setLocation(LgsLocation& location, const antlr4::Token* start, const antlr4::Token* stop) const;
};
