#pragma once
#include "LgsCodeGen.h"
#include "logos/LgsStack.h"

class LgsMetaSelection;
class LgsMatrixExpr;
class LgsEnvVar;
struct LgsPaths;
class LgsTernaryExpr;
class LgsMainFunc;
class LgsInterfaceFile;
class LgsTestFile;
class LgsObjectFile;
class LgsVectorExpr;
class LgsPostfixExpr;
class LgsDeferStmt;
class LgsInfiniteLoop;
class LgsObject;
class LgsWhileLoop;
class LgsFuncType;
class LgsIterable;
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
class LgsMetaVar;
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
struct LgsAppConfigs;

class LgsCgFile {
public:
    LgsStack stack;
    LgsCodeGen cg;
    LgsAppConfigs* appConfigs = nullptr;
    Value* startTime = nullptr;

    explicit LgsCgFile(const LgsCodeGenMode mode): cg(mode) {}
    bool generateSrcFile(LgsFile* file, const LgsPaths& paths);
    void visitMainFile(LgsMainFile* mainFile);
    void visitInterface(const LgsInterface* interface);
    void visitTestFile(const LgsTestFile* testFile);
    void visitObject(LgsObject* obj);
    void visitEnum(const LgsEnum* enum_);
    void visitMainFunc(LgsMainFunc* func);
    void visitFunc(LgsFunc* func);
    void visitExternalSymbols(LgsFile* file);

    // Statements
    void visitStmt(LgsStmt* stmt);
    void visitStmtsBlock(const LgsStmtsBlock* stmtsBlock);
    void visitLoop(LgsForLoop* loop);
    void visitRangeLoop(LgsRangeLoop* loop);
    void visitForeachLoop(LgsForeachLoop* loop);
    void visitInfiniteLoop(const LgsInfiniteLoop* loop);
    void visitLoopMetaVar(LgsMetaVar* metaVar);
    void visitWhileLoop(const LgsWhileLoop* loop);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(const LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitSimpleIf(LgsIfStmt* ifStmt);
    void visitIfWithElse(LgsIfStmt* ifStmt);
    void visitElseIf(LgsIfStmt* ifStmt);
    void visitSwitch(LgsSwitch* switchStmt);
    void visitContinueStmt();
    void visitReturnStmt(LgsReturn* returnStmt);
    void visitBreakStmt(const LgsBreak* breakStmt);
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitDeferStmt(const LgsDeferStmt* defer);
    void visitIOStmt(const LgsIOStmt* ioStmt);

    // Exprs
    void visitExpr(LgsExpr* expr);
    void visitBinaryExpr(LgsBinaryExpr* binExpr);
    void visitTernaryExpr(LgsTernaryExpr* ternaryExpr);
    void visitInstance(LgsInstance* instance);
    void visitConstant(LgsExpr* expr);
    void visitFloatConst(LgsFloatConst* floatConst);
    void visitIntConst(LgsIntConst* intConst);
    void visitStrConst(LgsStrConst* strConst);
    void visitCharConst(LgsCharConst* charConst);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitVariable(LgsVariable* variable);
    void visitNullableExpr(LgsNullableExpr* expr);
    void visitIterIndex(LgsIterIndex* iterIndex);
    void visitSelection(LgsSelection* selection);
    void visitFieldSelection(LgsVariable* var, LgsExpr* parent);
    void visitNullableSelection(LgsExpr* child, LgsExpr* parent);
    void visitMetaSelection(LgsMetaSelection* metaSelection);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitArrayExpr(LgsArrayExpr* arrayExpr);
    void visitStaticArray(LgsArrayExpr* arrayExpr);
    void visitDynamicArray(LgsArrayExpr* arrayExpr);
    void visitVectorExpr(LgsVectorExpr* vecExpr);
    void insertVecElement(LgsVectorExpr* vecExpr, Value* element, size_t i);
    void visitMatrixExpr(const LgsMatrixExpr* matrixExpr);
    void visitHashMap(LgsHashMap* hashMap);
    void visitEnvVar(LgsEnvVar* envVar);
    void visitCast(LgsCast* cast);
    void visitLambda(LgsFunc* func);

    // Funcs
    void createPrologue(LgsFunc* func);
    void createEpilogue(const LgsFunc* func);
    void initMainArgs(const LgsMainFunc* mainFunc);
    StructType* getThunkCtxType(const LgsFuncCall* fc);
    Value* getThunkCtx(const LgsFuncCall* fc, Type* ctxTy);
    Function* getThunkFunc(LgsFuncCall* fc, Type* ctxTy);

    void moveValue(LgsType* type, Value* left, Value* right);
    void createVecField(LgsField* field, Value* parent);
    bool checkMock(LgsExpr* expr);
    void getMapFunc(LgsFuncType* mapFunc);
    void getFilterFunc(LgsFuncType* filterFunc);
    void getForeachFunc(LgsFuncType* forEachFunc);
};
