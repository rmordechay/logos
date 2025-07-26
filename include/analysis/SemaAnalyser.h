#pragma once
#include "utils/LgsASTVisitor.h"
#include "utils/LgsErrHandler.h"
#include "loops/LgsInfiniteLoop.h"

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
class LgsPatternMatch;
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

class SemaAnalyser final : public LgsASTVisitor {
public:
    LgsStack stack;
    LgsErrHandler errHandler;
    LgsSymbolTable& globals;

    explicit SemaAnalyser(LgsFile* file, LgsSymbolTable& globals) : LgsASTVisitor(file), globals(globals) {}
    void analyse() override;
    void visitMainFile(LgsMainFile* mainFile) override;
    void visitSingleton(LgsObject* obj);
    void visitObject(LgsObject* obj) override;
    void visitInterface(LgsInterface* interface) override;
    void visitField(LgsField* field) override;
    void visitFunc(LgsFunc* func) override;
    void visitParam(LgsParam* param) override;
    void visitStmt(LgsStmt* stmt) override;
    void visitStmtBlock(LgsStmtsBlock* stmtBlock) override;
    void visitAssignment(LgsAssignment* assignment) override;
    void visitVarDec(LgsVarDec* varDec) override;
    void visitIfStmt(LgsIfStmt* ifStmt) override;
    void visitPatternMatch(LgsPatternMatch* patternMatching) override;
    void visitBoolPatternMatching(const LgsPatternMatch* patternMatching) override;
    void visitLoopStmt(LgsForLoop* loopStmt) override;
    void visitRangeLoop(const LgsRangeLoop* rangeLoop) override;
    void visitForeachLoop(LgsForeachLoop* foreachLoop) override;
    void visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop);
    void visitReturnStmt(const LgsReturn* returnStmt) override;
    void visitBreakStmt(const LgsBreakStmt* breakStmt) override;
    void visitContinueStmt(const LgsContinueStmt* continueStmt) override;
    void visitEnum(const LgsEnum* lgsEnum) const override;
    void visitExpr(LgsExpr* expr) override;
    void visitCast(LgsCast* castExpr) override;
    void visitArrayExpr(LgsArrayExpr* array) override;
    void visitStaticArray(const LgsArrayExpr* arrayExpr);
    void visitDynamicArray(const LgsArrayExpr* array);
    void visitHashMap(LgsHashMap* hashMap) override;
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr) override;
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr) override;
    void visitVariable(LgsVariable* variable) override;
    void visitFuncCall(LgsFuncCall* funcCall) override;
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitAnonymousFunc(LgsFuncCall* funcCall, LgsFuncType* funcType) override;
    void visitMethodCall(LgsFuncCall* methodCall, LgsType* parentType) override;
    void visitSelection(LgsSelection* selection) override;
    void visitInnerSelections(const LgsSelection* selection) override;
    void visitFieldSelection(const LgsExpr* parentExpr, LgsVariable* childField) override;
    void visitFirstSelection(LgsExpr* firstExpr) override;
    void visitInstance(LgsInstance* instance) override;
    void visitIterIndex(LgsIterIndex* iterIndex) override;
    void visitSlice(LgsIterIndex* iterIndex) override;
    void visitGroup(LgsGroup* group) const override;

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

    LgsSymbol* getSymbol(const string& name, const Location* location);
    void addLocalSymbol(const string& name, const LgsSymbol& newSymbol);
    void resolveFuncCall(LgsFuncCall* funcCall);
    bool resolveMethodCall(LgsFuncCall* methodCall, LgsType* parentType);
    static void inferBaseType(const LgsArrayExpr* array);
    LgsType* resolveType(LgsType* type);
    void resolveIterable(LgsIterable* iterable);
    void resolveFuncTypes(LgsFuncType* funcType);
    void resolveObjTypes(LgsObject* obj);
    void resolveInterfaceTypes(LgsInterface* interface);
    void resolveGroupTypes(LgsGroup* group);
    static string getMissingImplementsStr(const vector<LgsField*>& fields, const vector<LgsFunc*>& methods);
    ~SemaAnalyser() override = default;
};
