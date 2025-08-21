#pragma once
#include "../symbols/exprs/unary/LgsVectorExpr.h"
#include "logos/LgsStack.h"
#include "utils/LgsErrHandler.h"
#include "analysis/LgsTypeResolver.h"

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

class LgsSema final {
public:
    LgsStack stack;
    LgsFile* file = nullptr;
    LgsErrHandler errHandler;
    LgsSymbolTable& globals;
    LgsTypeResolver typeResolver;

    explicit LgsSema(LgsFile* file, LgsSymbolTable& globals) : file(file), globals(globals), typeResolver(errHandler, globals) {}
    void analyse();
    void visitMainFile(LgsMainFile* mainFile);
    void visitObject(LgsObject* obj);
    void visitInterface(LgsInterface* interface);
    void visitField(LgsField* field);
    void visitFunc(LgsFunc* func);
    void visitParam(LgsParam* param);
    void visitStmt(LgsStmt* stmt);
    void visitStmtsBlock(LgsStmtsBlock* stmtsBlock);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitPatternMatching(LgsIfStmt* pm);
    void visitBoolPatternMatching(LgsIfStmt* pm);
    void visitWhileLoop(LgsWhileLoop* whileLoop);
    void visitLoopStmt(LgsForLoop* loopStmt);
    void visitRangeLoop(const LgsRangeLoop* rangeLoop);
    void visitForeachLoop(LgsForeachLoop* foreachLoop);
    void visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop);
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitReturnStmt(LgsReturn* returnStmt);
    void visitContinueStmt(LgsContinue* continueStmt);
    void visitBreakStmt(LgsBreak* breakStmt);
    void visitDeferStmt(const LgsDeferStmt* deferStmt);
    void visitInterfaceInstance(LgsInstance* instance, LgsInterface* interface);
    void visitExpr(LgsExpr* expr);
    void visitCast(LgsCast* castExpr);
    void visitArrayExpr(LgsArrayExpr* array);
    void visitStaticArray(LgsArrayExpr* arrayExpr);
    void visitDynamicArray(LgsArrayExpr* array);
    void visitHashMap(LgsHashMap* hashMap);
    void visitVector(const LgsVectorExpr* vec);
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitVariable(LgsVariable* variable);
    void visitSelection(LgsSelection* selection);
    void visitFirstSelection(LgsExpr* firstExpr);
    void visitInnerSelections(const LgsSelection* selection);
    void visitFieldSelection(LgsVariable* child, LgsType* parentType);
    void visitMethodCall(LgsFuncCall* methodCall, LgsType* parentType);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitStrConst(const LgsStrConst* strConst);
    void visitInstance(LgsInstance* instance);
    void visitIterIndex(LgsIterIndex* iterIndex);
    void visitSlice(LgsIterIndex* iterIndex);
    void visitGroup(LgsGroup* group);
    void visitForIsFirst(LgsVariable* variable);
    void visitForIsLast(LgsVariable* variable);

    void validateObjImplements(LgsObject* obj, const std::vector<LgsType*>& interfaces);
    void validateObjInterface(LgsObject* obj, LgsInterface* interface);
    void validateArgs(const LgsFuncCall* funcCall);
    void validateIndex(LgsIterIndex* iterIndex);
    void validateSliceBounds(LgsIterIndex* iterIndex);
    bool validateFieldVisibility(LgsField* field, const LgsObject* parent);
    bool validateMethodVisibility(LgsFuncCall* methodCall, const LgsObject* parent);
    static bool validateBlockControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func);

    void castExprToType(LgsExpr* expr, LgsType* toType);
    void matchExprToType(LgsExpr* expr, LgsType* type);
    void resolveFuncCall(LgsFuncCall* funcCall);
    bool resolveMethodCall(LgsFuncCall* methodCall, LgsType* parentType);
    bool resolveLoopVars(LgsForeachLoop* foreachLoop, LgsUnaryExpr* iterExpr, const LgsIterable* iterable);
    void resolveScalars(LgsVariable* fieldVar, LgsVec* vec);
    LgsSymbol* getSymbol(const std::string& name, LgsLocation* location);
    void addLocalSymbol(const LgsSymbol& newSymbol);
};

