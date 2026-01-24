#pragma once
#include "LgsCodeGen.h"
#include "exprs/LgsNullableExpr.h"
#include "files/LgsFile.h"
#include "logos/LgsStack.h"

class LgsMetaSelection;
class LgsJson;
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

class LgsCgModule {
public:
    LgsFile* file;
    LgsStack stack;
    LgsCodeGen& cg;
    LgsPaths& paths;
    LgsGlobals& globals;
    LgsAppConfigs& appConfigs;
    Value* startTime = nullptr;

    explicit LgsCgModule(LgsFile* file, LgsAppConfigs& appConfigs, LgsGlobals& globals, LgsPaths& paths)
        : file(file), cg(file->cg), paths(paths), globals(globals), appConfigs(appConfigs) {
    }

    bool generate();
    void visitMainFile(LgsMainFile* mainFile);
    void visitInterface(const LgsInterface* interface);
    void visitTestFile(const LgsTestFile* testFile);
    void visitObject(LgsObject* obj);
    void visitEnum(const LgsEnum* enum_);
    void visitMainFunc(LgsMainFunc* func);
    void visitFunc(LgsFunc* func);
    void visitExternalSymbols();
    void visitStmt(LgsStmt* stmt);
    void visitStmtsBlock(const LgsStmtsBlock* stmtsBlock);
    void visitLoop(LgsForLoop* loop);
    void visitRangeLoop(LgsRangeLoop* loop);
    void visitForeachLoop(LgsForeachLoop* loop);
    void visitInfiniteLoop(const LgsInfiniteLoop* loop) const;
    void visitLoopMetaVar(LgsMetaVar* metaVar) const;
    void visitWhileLoop(const LgsWhileLoop* loop);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(const LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitSimpleIf(LgsIfStmt* ifStmt);
    void visitIfWithElse(LgsIfStmt* ifStmt);
    void visitElseIf(LgsIfStmt* ifStmt);
    void visitSwitch(LgsSwitch* switchStmt);
    void visitContinueStmt() const;
    void visitReturnStmt(LgsReturn* returnStmt);
    void visitBreakStmt(const LgsBreak* breakStmt) const;
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitDeferStmt(const LgsDeferStmt* defer);
    void visitIOStmt(const LgsIOStmt* ioStmt);
    void visitExpr(LgsExpr* expr, bool assign = false);
    void visitBinaryExpr(LgsBinaryExpr* binExpr);
    void visitTernaryExpr(LgsTernaryExpr* ternaryExpr);
    void visitCast(LgsCast* cast);
    void visitLambda(LgsFunc* func);
    void visitConstant(LgsExpr* expr);
    void visitFloatConst(LgsFloatConst* floatConst) const;
    void visitComplexConst(const LgsComplexConst* complex);
    void visitNullableExpr(LgsNullableExpr* expr);
    void visitArrayExpr(LgsArrayExpr* arrayExpr);
    void visitStaticArray(LgsArrayExpr* arrayExpr) const;
    void visitDynamicArray(LgsArrayExpr* arrayExpr) const;
    void visitVectorExpr(LgsVectorExpr* vectorExpr);
    void visitMatrixExpr(const LgsMatrixExpr* matrixExpr);
    void visitHashMap(LgsHashMap* hashMap);
    void visitEnvVar(LgsEnvVar* envVar) const;
    void visitVariable(LgsVariable* variable);
    void visitSelection(LgsSelection* selection, bool assign = false);
    void visitFieldSelection(LgsVariable* var, LgsExpr* parent) const;
    void visitNullableSelection(LgsExpr* child, LgsExpr* parent) const;
    void visitMetaSelection(LgsMetaSelection* metaSelection);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitIntConst(LgsIntConst* intConst) const;
    void visitStrConst(LgsStrConst* strConst);
    void visitCharConst(LgsCharConst* charConst) const;
    void visitInstance(LgsInstance* instance);
    void visitIterIndex(LgsIterIndex* iterIndex, bool assign);
    void visitJson(LgsJson* json);

    // Funcs
    void createPrologue(LgsFunc* func);
    void createEpilogue(const LgsFunc* func) const;
    void initMainArgs(const LgsMainFunc* mainFunc) const;
    StructType* getThunkCtxType(const LgsFuncCall* fc) const;
    Value* getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) const;
    Function* getThunkFunc(LgsFuncCall* fc, Type* ctxTy) const;

    void initVirtuals();
    void addVirtualFields(LgsObject* obj, Value* ptr) const;
    void createVecField(LgsField* field, Value* parent) const;
    bool checkMock(LgsExpr* expr) const;
    void generateMapFunc(LgsFuncType* mapFunc);
    void generateFilterFunc(LgsFuncType* filterFunc);
    void generateForeachFunc(LgsFuncType* forEachFunc) const;
};
