#pragma once
#include "LgsLLVMGen.h"
#include "files/LgsFile.h"
#include "logos/LgsStack.h"

class LgsTernaryExpr;
class LgsMainFunc;
class LgsInterfaceFile;
class LgsObjectFile;
class LgsVectorExpr;
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
class LgsFloatConst;
class LgsBreak;
class LgsReturn;
class LgsForeachLoop;
class LgsRangeLoop;
class LgsStmtsBlock;
class LgsLoopMetaVar;
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
class LgsIntConst;
class LgsForLoop;
class LgsTypeExpr;
class LgsIOStmt;
struct LgsSymbol;
struct LgsIndex;

class LgsCodeGen {
public:
    LgsFile& file;
    LgsStack stack;
    LgsLLVMGen& cg;
    Function* currentIRFunc = nullptr;
    Function* mapFunc = nullptr;
    static std::atomic<size_t> namesCounter;

    explicit LgsCodeGen(LgsFile& file) : file(file), cg(file.generator) {}
    void generate(const LgsAppConfigs& appConfigs, TargetMachine& targetMachine);
    void visitMainFile(LgsMainFile* mainFile);
    void visitObjFile(const LgsObjectFile* objFile);
    void visitInterfaceFile(const LgsInterfaceFile* interfaceFile);
    void visitTestFile(const LgsTestFile* testFile);
    void visitMainFunc(LgsMainFunc* func);
    void visitFunc(LgsFunc* func);
    void visitField(LgsField* field) const;
    void visitParam(LgsParam* param);
    void visitStmt(LgsStmt* stmt);
    void visitStmtsBlock(const LgsStmtsBlock* stmtsBlock);
    void visitLoop(LgsForLoop* loop);
    void visitRangeLoop(LgsRangeLoop* loop);
    void visitForeachLoop(LgsForeachLoop* loop);
    void visitInfiniteLoop(const LgsInfiniteLoop* loop) const;
    void visitLoopMetaVar(LgsLoopMetaVar* metaVar) const;
    void visitWhileLoop(const LgsWhileLoop* loop);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(const LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitSimpleIf(LgsIfStmt* ifStmt);
    void visitIfWithElse(LgsIfStmt* ifStmt);
    void visitElseIf(LgsIfStmt* ifStmt);
    void visitPatternMatch(LgsPatternMatch* pm);
    void visitContinueStmt();
    void visitReturnStmt(LgsReturn* returnStmt);
    void visitBreakStmt(const LgsBreak* breakStmt);
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitDeferStmt(const LgsDeferStmt* deferStmt);
    void visitIOStmt(const LgsIOStmt* ioStmt);
    void visitExpr(LgsExpr* expr);
    void visitBinaryExpr(LgsBinaryExpr* binExpr);
    void visitTernaryExpr(LgsTernaryExpr* ternaryExpr);
    void visitCast(LgsCast* cast);
    void visitLambda(LgsFunc* func);
    void visitIntConst(LgsIntConst* intConst) const;
    void visitFloatConst(LgsFloatConst* floatConst) const;
    void visitArrayExpr(LgsArrayExpr* array);
    void visitHashMap(LgsHashMap* hashMap);
    void visitVectorExpr(LgsVectorExpr* vectorExpr);
    void visitVariable(LgsVariable* variable);
    void visitSelection(LgsSelection* selection);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitIterFunc(const LgsFuncCall* funcCall);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitStrConst(LgsStrConst* strConst);
    void visitIterIndex(LgsIterIndex* iterIndex, bool inAssignment = false);
    void visitInstance(LgsInstance* instance);
    void visitJson(LgsJson* json);
    void visitNullableExpr(LgsNullableExpr* nullableExpr);

    void initFields(LgsInstance* instance);
    bool checkMock(LgsExpr* expr);
    void yield() const;

    // Funcs
    void createPrologue(LgsFunc* func);
    void createEpilogue(LgsFunc* func);
    void initMainArgs(LgsMainFunc* mainFunc);
    Value* getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) const;
    Type* getThunkCtxType(const LgsFuncCall* fc) const;
    Function* getThunkFunc(const LgsFuncCall* fc, Type* ctxTy) const;

    // If stmt
    void generateIf(Value* cond, const std::function<void()>& blockStmtCb) const;

    // Iterables
    void setStaticArray(LgsArrayExpr* arrayExpr);
    void setNestedSArr(const LgsArrayExpr* arrayExpr, Type* parentType, Value* parentValue, const std::vector<Value*>& indices);
    void setDynamicArray(LgsArrayExpr* arrayExpr);
    void setSetExpr(LgsArrayExpr* arrayExpr);
    void createMapFunc(LgsFunc* func);
    void createFilterFunc(LgsFunc* func);

    Value* getIRValue(LgsValue* value);
    bool allArgsAreConst(const std::vector<LgsExpr*>& args);
};
