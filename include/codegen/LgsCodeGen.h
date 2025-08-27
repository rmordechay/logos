#pragma once
#include "LgsLLVM.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "files/LgsFile.h"
#include "logos/LgsStack.h"

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
class LgsGroup;
class LgsValue;
class LgsVariable;
class LgsUnaryExpr;
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

class LgsCodeGen {
public:
    LgsFile& file;
    LgsStack stack;
    LgsLLVM& cg;
    Function* currentIRFunc = nullptr;

    explicit LgsCodeGen(LgsFile& file) : file(file), cg(file.generator) {}
    void generate(const LgsAppConfigs& appConfigs, TargetMachine& targetMachine);
    void visitMainFile(LgsMainFile* mainFile);
    void visitObjFile(const LgsObjectFile* objFile);
    void visitInterfaceFile(const LgsInterfaceFile* interfaceFile);
    void visitMainFunc(LgsMainFunc* func);
    void visitFunc(LgsFunc* func);
    void visitObject(LgsObject* obj) const;
    void visitInterface(LgsInterface* interface) const;
    void visitGroup(LgsGroup* group);
    void visitField(LgsField* field) const;
    void visitParam(LgsParam* param);
    void visitLoop(LgsForLoop* loop);
    void visitRangeLoop(LgsRangeLoop* loop);
    void visitForeachLoop(LgsForeachLoop* loop);
    void visitInfiniteLoop(const LgsInfiniteLoop* loop) const;
    void visitWhileLoop(const LgsWhileLoop* loop);
    void visitLoopMetaVar(LgsLoopMetaVar* metaVar);
    void visitStmt(LgsStmt* stmt);
    void visitStmtsBlock(const LgsStmtsBlock* stmtsBlock);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(const LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitSimpleIf(LgsIfStmt* ifStmt);
    void visitIfWithElse(LgsIfStmt* ifStmt);
    void visitElseIf(LgsIfStmt* ifStmt);
    void visitPatternMatching(LgsIfStmt* pm);
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitReturnStmt(LgsReturn* returnStmt);
    void visitContinueStmt();
    void visitBreakStmt(const LgsBreak* breakStmt);
    void visitDeferStmt(const LgsDeferStmt* deferStmt);
    void visitExpr(LgsExpr* expr);
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr);
    void visitBinaryExpr(LgsBinaryExpr* binExpr);
    void visitCast(LgsCast* lgsCast);
    void visitLambda(LgsFunc* func);
    void visitIntConst(LgsIntConst* intConst) const;
    void visitArrayExpr(LgsArrayExpr* array);
    void visitHashMap(LgsHashMap* hashMap);
    void visitVectorExpr(LgsVectorExpr* vec);
    void visitVariable(LgsVariable* variable);
    void visitSelection(LgsSelection* selection);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr) const;
    void visitStrConst(LgsStrConst* strConst) const;
    void visitTypeExpr(LgsTypeExpr* typeExpr);
    void visitIterIndex(LgsIterIndex* iterIndex);
    void visitInstance(LgsInstance* instance);
    void initFields(LgsInstance* instance);

    // Funcs
    void initMainArgs(LgsMainFunc* mainFunc);
    void createPrologue(LgsFunc* func);
    void createEpilogue(LgsFunc* func);
    void freeHeap(const LgsFunc* func);
    Value* getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) const;
    Type* getThunkCtxType(const LgsFuncCall* fc) const;
    Function* getThunkFunc(const LgsFuncCall* fc, Type* ctxTy) const;

    // If stmt
    void generateIf(Value* cond, const std::function<void()>& blockStmtCb) const;

    // Iterables
    Value* createConstArray(const LgsArrayExpr* arrayExpr);
    Value* createDynamicArray(LgsArrayExpr* arrayExpr);
    void initIterator(LgsIterator* iterator);
    Value* iterNext(LgsIterator* iterator);
    Value* iterHasNext(LgsIterator* iterator);

    // Assignment
    void createIRAssignment(const LgsAssignment* assignment) const;

    // Generic
    Value* getIRValue(LgsValue* value);
};
