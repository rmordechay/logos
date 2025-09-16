#pragma once
#include "../symbols/test/LgsMock.h"
#include "exprs/LgsVectorExpr.h"
#include "logos/LgsStack.h"
#include "utils/LgsErrHandler.h"
#include "analysis/LgsTypeResolver.h"
#include "loops/LgsLoopMetaVar.h"
#include "stmts/LgsIOPair.h"
#include "stmts/LgsIOStmt.h"

#include <vector>

class LgsTest;
class LgsInterfaceFile;
class LgsObjectFile;
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
    void visitTestFile(const LgsTestFile* testFile);
    void visitField(LgsField* field);
    void visitFunc(LgsFunc* func);
    void visitLambda(LgsFunc* lambda);
    void visitParam(LgsParam* param);
    void visitIOPair(LgsIOPair* ioPair, LgsObject* obj);
    void visitTest(const LgsTest* test);
    void visitStmt(LgsStmt* stmt);
    void visitStmtsBlock(LgsStmtsBlock* stmtsBlock);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(const LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitPatternMatching(LgsIfStmt* pm);
    void visitBoolPatternMatching(LgsIfStmt* pm);
    void visitWhileLoop(const LgsWhileLoop* whileLoop);
    void visitLoopStmt(LgsForLoop* loopStmt);
    void visitRangeLoop(LgsRangeLoop* rangeLoop);
    void visitForeachLoop(const LgsForeachLoop* foreachLoop);
    void visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop);
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitReturnStmt(LgsReturn* returnStmt);
    void visitIOStmt(const LgsIOStmt* ioStmt);
    void visitContinueStmt(const LgsContinue* continueStmt);
    void visitBreakStmt(const LgsBreak* breakStmt);
    void visitDeferStmt(const LgsDeferStmt* deferStmt);
    void visitExpr(LgsExpr* expr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitCast(LgsCast* lgsCast);
    void visitArrayExpr(LgsArrayExpr* array);
    void visitStaticArray(LgsArrayExpr* arrayExpr);
    void visitDynamicArray(LgsArrayExpr* array);
    void visitHashMap(LgsHashMap* hashMap);
    void visitVectorExpr(const LgsVectorExpr* vectorExpr);
    void visitVariable(LgsVariable* variable);
    void visitSelection(LgsSelection* selection);
    void visitFirstSelection(LgsExpr* firstExpr);
    void visitInnerSelections(const LgsSelection* selection);
    void visitFieldSelection(LgsVariable* child, LgsType* parentType);
    void visitIterIndexSelection(LgsIterIndex* child, LgsType* parentType);
    void visitMethodCall(LgsFuncCall* methodCall, LgsExpr* parent);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitStrConst(const LgsStrConst* strConst);
    void visitTypeExpr(LgsTypeExpr* typeExpr);
    void visitInstance(LgsInstance* instance);
    void visitInterfaceInstance(LgsInstance* instance, LgsInterface* interface);
    void visitIterIndex(LgsIterIndex* iterIndex);
    void visitIndex(LgsIterIndex* iterIndex);
    void visitSlice(LgsIterIndex* iterIndex);
    void visitGroup(LgsGroup* group);
    void visitLoopMetaVar(LgsLoopMetaVar* metaVar);

    void matchExprToType(const LgsExpr* expr, LgsType* type);
    void resolveFuncCall(LgsFuncCall* funcCall);
    bool resolveForeachVars(const LgsForeachLoop* foreachLoop);
    void addHeapExpr(LgsExpr* expr);

    void validateObjImplements(LgsObject* obj, const std::vector<LgsType*>& interfaces);
    void validateObjInterface(LgsObject* obj, LgsInterface* interface);
    void validateIndex(LgsIterIndex* iterIndex);
    void validateSliceBounds(LgsIterIndex* iterIndex);
    bool validateFieldVisibility(LgsField* field, const LgsObject* parent);
    bool validateMethodVisibility(const LgsFuncCall* methodCall, const LgsObject* parent);
    bool validateVecElements(const LgsVariable* fieldVar, LgsVec* vec);
    void validateTypeDuplicates(LgsType* type);
    void validateMock(const LgsSelection* selection);
    static bool validateBlockControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func);

    LgsSymbol* getSymbol(const std::string& name, const LgsLocation* location);
    void addLocalSymbol(const LgsSymbol& newSymbol);
};

