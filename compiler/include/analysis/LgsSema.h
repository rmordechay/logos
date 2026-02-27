#pragma once
#include <unordered_map>
#include <string>
#include <vector>

#include "logos/LgsStack.h"
#include "analysis/LgsTypeResolver.h"
#include "files/LgsEnvFile.h"
#include "errors/LgsErrHandler.h"
#include "exprs/LgsFuncCall.h"
#include "stmts/LgsAssignment.h"

class LgsMainFunc;
class LgsMetaSelection;
class LgsAppFile;
class LgsTernaryExpr;
class LgsVec;
class LgsInterfaceFile;
class LgsObjectFile;
class LgsTestFile;
class LgsPostfixExpr;
class LgsDeferStmt;
class LgsInfiniteLoop;
class LgsObject;
class LgsWhileLoop;
class LgsFuncType;
class LgsIterable;
class LgsFile;
class LgsCoroutine;
class LgsPrefixExpr;
class LgsDArray;
class LgsValue;
class LgsVariable;
class LgsStrConst;
class LgsHashMap;
class LgsExpr;
class LgsType;
class LgsContinue;
class LgsBreak;
class LgsReturn;
class LgsForeachLoop;
class LgsRangeLoop;
class LgsStmtsBlock;
class LgsStmt;
class LgsMainFile;
class LgsApp;
class LgsCast;
class LgsVarDec;
class LgsInstance;
class LgsIterIndex;
class LgsSelection;
class LgsFuncCall;
class LgsBinaryExpr;
class LgsArrayExpr;
class LgsIfStmt;
class LgsAssignment;
class LgsForLoop;
struct LgsSymbol;
struct LgsIndex;
class LgsEnum;
class LgsField;
class LgsFunc;
class LgsIOPair;
class LgsIOStmt;
class LgsInterface;
class LgsMatrixExpr;
class LgsMetaVar;
class LgsModuleExpr;
class LgsNullableExpr;
class LgsParam;
class LgsStmtWrapper;
class LgsSwitch;
class LgsVectorExpr;
struct LgsAppConfigs;
struct LgsBaseMsg;
struct LgsLocation;
struct LgsSymbolTable;


class LgsSema final {
public:
    LgsFile* file;
    LgsStack stack;
    LgsAppConfigs& appConfigs;
    LgsSymbolTable& globals;
    LgsErrHandler errHandler;
    LgsTypeResolver typeResolver;
    LgsObject* currentObj = nullptr;
    std::vector<LgsApp*> importApps;

    explicit LgsSema(LgsAppConfigs& appConfigs, LgsFile* file, LgsSymbolTable& globals, const std::vector<LgsApp*>& importApps)
        : file(file), appConfigs(appConfigs), globals(globals), typeResolver(file, errHandler, globals), importApps(importApps) {}

    void analyse();
    void visitMainFile(LgsMainFile* mainFile);
    void visitTestFile(const LgsTestFile* testFile);
    bool isTypeRecursive(const LgsType* type);
    void visitObject(LgsObject* obj);
    void visitInterface(LgsInterface* interface);
    void visitEnum(LgsEnum* enum_);
    void visitField(LgsField* field);
    void visitFuncHeader(LgsFuncType* ft);
    void visitFunc(LgsFunc* func);
    void visitMainFunc(LgsMainFunc* mainFunc);
    void visitLambda(LgsFunc* lambda);
    void visitObjImplements(LgsObject* obj, const std::vector<LgsType*>& interfaces);
    void visitParam(LgsParam* param);
    void visitIOPair(LgsIOPair* ioPair, LgsObject* obj);
    void visitStmt(LgsStmtWrapper& stmt);
    void visitStmtsBlock(LgsStmtsBlock* stmtsBlock);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(const LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitMacroIf(LgsIfStmt* ifStmt);
    void visitSwitch(LgsSwitch* switchStmt);
    void visitLoop(LgsForLoop* loopStmt);
    void visitRangeLoop(LgsRangeLoop* rangeLoop);
    void visitForeachLoop(LgsForeachLoop* foreachLoop);
    void visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop);
    void visitWhileLoop(const LgsWhileLoop* whileLoop);
    void visitReturnStmt(LgsReturn* returnStmt);
    void visitContinueStmt(LgsContinue* continueStmt);
    void visitBreakStmt(LgsBreak* breakStmt);
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitDeferStmt(const LgsDeferStmt* deferStmt);
    void visitIOStmt(LgsIOStmt* ioStmt);
    void visitExpr(LgsExpr* expr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitTernaryExpr(LgsTernaryExpr* ternary);
    void visitCast(LgsCast* cast);
    void visitNullableExpr(LgsNullableExpr* nullableExpr);
    void visitArrayExpr(LgsArrayExpr* arrayExpr);
    void visitHashMap(LgsHashMap* hashMap);
    void visitVectorExpr(LgsVectorExpr* vectorExpr);
    void visitMatrixExpr(const LgsMatrixExpr* matrixExpr);
    void visitVariable(LgsVariable* variable);
    void visitSelection(LgsSelection* selection);
    void visitInnerSelections(const LgsSelection* selection);
    void visitFieldSelection(LgsVariable* child, LgsExpr* parent);
    void visitIterIndexSelection(LgsIterIndex* iterIndex, LgsType* parentType);
    void visitMetaSelection(LgsMetaSelection* metaSelection, LgsExpr* parent = nullptr);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitMethodCall(LgsFuncCall* methodCall, LgsExpr* parent);
    bool visitFuncArgs(LgsFuncCall* funcCall, LgsFuncType* ft);
    void visitArg(bool isMixed, LgsVarDec& varDec, const LgsParam* param, const LgsLocation& location);
    void visitModuleExpr(LgsModuleExpr* moduleExpr);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitStrConst(const LgsStrConst* strConst);
    void visitInstance(LgsInstance* instance);
    void visitUnwrap(LgsExpr* expr);
    void visitInlineInterface(LgsInstance* instance, LgsInterface* interface);
    void visitIterIndex(LgsIterIndex* iterIndex);
    void visitIndex(LgsIterIndex* iterIndex);
    void visitLoopMetaVar(LgsMetaVar* metaVar);

    bool validateExprType(const LgsExpr* expr, LgsType* type);
    bool validateTypeName(const std::string& name, const LgsLocation& location);
    bool validateLocalName(const std::string& name, const LgsLocation& location);
    void validateIndex(const LgsIterIndex* iterIndex);
    bool validateFieldVisibility(LgsField* field, LgsType* parent, const LgsLocation& location);
    bool validateMethodVisibility(const LgsFunc* method, LgsType* parent, const LgsLocation& location);
    bool validateVecElements(const LgsVariable* fieldVar, LgsVec* vec);
    void validateObjDuplicates(LgsObject* obj);
    static bool validateControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func);

    void setFunc(LgsFuncCall* funcCall, LgsFunc* func);
    void addTypeReplacement(LgsType* genericType, LgsType* replacement, std::unordered_map<std::string, LgsType*>& replacements);
    static void replaceGenericFunc(LgsFunc* newFunc, const std::unordered_map<std::string, LgsType*>& replacements);
    static void replaceGenerics(LgsType*& type, const std::unordered_map<std::string, LgsType*>& replacements);
    void replaceForLoop(LgsStmtWrapper& stmt);
    LgsSymbol* getSymbol(const std::string& name);
    void addLocalSymbol(const LgsSymbol& newSymbol);
    void createCoroutineFunc(LgsFuncCall* funcCall);
    void addError(const LgsBaseMsg& lgsErr, const LgsLocation& location, const std::vector<std::string>& args = {});
    void addGenericType(LgsType* type) const;
    void addRTType(LgsType* type) const;
};
