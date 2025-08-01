#pragma once
#include "utils/LgsErrHandler.h"
#include "loops/LgsInfiniteLoop.h"

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
class LgsContinueStmt;
class LgsBreakStmt;
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

class SemaAnalyser final {
public:
    LgsStack stack;
    LgsFile* file = nullptr;
    LgsErrHandler errHandler;
    LgsSymbolTable& globals;

    explicit SemaAnalyser(LgsFile* file, LgsSymbolTable& globals) : file(file), globals(globals) {}
    void analyse();
    void visitMainFile(LgsMainFile* mainFile);
    void visitObject(LgsObject* obj);
    void visitInterface(LgsInterface* interface);
    void visitField(const LgsField* field);
    void visitFunc(LgsFunc* func);
    void visitParam(LgsParam* param);
    void visitStmt(LgsStmt* stmt);
    void visitStmtsBlock(LgsStmtsBlock* stmtsBlock);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(const LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitPatternMatching(LgsIfStmt* pm);
    void visitBoolPatternMatching(LgsIfStmt* pm);
    void visitLoopStmt(LgsForLoop* loopStmt);
    void visitRangeLoop(const LgsRangeLoop* rangeLoop);
    void visitForeachLoop(LgsForeachLoop* foreachLoop);
    void visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop);
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitReturnStmt(const LgsReturn* returnStmt);
    void visitExpr(LgsExpr* expr);
    void visitCast(LgsCast* castExpr);
    void visitArrayExpr(const LgsArrayExpr* array);
    void visitStaticArray(const LgsArrayExpr* arrayExpr);
    void visitDynamicArray(const LgsArrayExpr* array);
    void visitHashMap(const LgsHashMap* hashMap);
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitVariable(LgsVariable* variable);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitAnonymousFunc(LgsFuncCall* funcCall, LgsFuncType* funcType);
    void visitMethodCall(LgsFuncCall* methodCall, LgsType* parentType);
    void visitSelection(LgsSelection* selection);
    void visitInnerSelections(const LgsSelection* selection);
    void visitFieldSelection(LgsVariable* childField, LgsType* parentType);
    void visitFirstSelection(LgsExpr* firstExpr);
    void visitInstance(LgsInstance* instance);
    void visitIterIndex(LgsIterIndex* iterIndex);
    void visitSlice(LgsIterIndex* iterIndex);
    void visitGroup(LgsGroup* group) const;

    void setBinaryExprType(LgsBinaryExpr* binaryExpr);
    bool setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable);
    bool setLoopVars(LgsForeachLoop* foreachLoop, LgsUnaryExpr* iterExpr, const LgsIterable* iterable);

    void validateInterfaces(LgsObject* obj, const vector<LgsType*>& interfaces);
    void validateImplements(LgsObject* type, LgsInterface* interface);
    void validateExprType(const LgsExpr* expr, LgsType* type);
    void validateIndex(LgsIterIndex* iterIndex);
    void validateSliceBounds(LgsIterIndex* iterIndex);
    bool validateFieldVisibility(LgsField* field, const LgsObject* parent);
    bool validateMethodVisibility(const LgsFuncCall* methodCall, const LgsObject* parent);
    void validateFuncControlFlow(const LgsFunc* func);
    static bool validateBlockControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func);

    LgsSymbol* getSymbol(const string& name, const LgsLocation* location);
    void addLocalSymbol(const LgsSymbol& newSymbol);
    void resolveFuncCall(LgsFuncCall* funcCall);
    bool resolveMethodCall(LgsFuncCall* methodCall, LgsType* parentType);
    LgsType* resolveType(LgsType* type);
    void resolveIterable(LgsIterable* iterable);
    void resolveFuncTypes(LgsFuncType* funcType);
    void resolveObjTypes(LgsObject* obj);
    void resolveInterfaceTypes(LgsInterface* interface);
    void resolveGroupTypes(LgsGroup* group);
    ~SemaAnalyser() = default;
};
