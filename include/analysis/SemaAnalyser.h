#pragma once
#include "files/LgsFile.h"
#include "logos/LgsASTVisitor.h"
#include "logos/LgsErrHandler.h"
#include "loops/LgsInfiniteLoop.h"

class LgsArray;
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
class LgsStmtBlock;
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

    explicit SemaAnalyser(LgsFile* file) : LgsASTVisitor(file) {}
    void start() override;
    void visitMainFile(LgsMainFile* mainFile) override;
    void visitObject(LgsObject* obj) override;
    void visitInterface(LgsInterface* interface) const override;
    void visitObjectImplements(LgsObject* obj);
    void visitField(LgsField* field) override;
    void visitFunc(LgsFunc* func) override;
    void visitParam(LgsParam* param) override;
    void visitStmt(LgsStmt* stmt) override;
    void visitStmtBlock(LgsStmtBlock* stmtBlock) override;
    void visitAssignment(LgsAssignment* assignment) override;
    void visitVarDec(LgsVarDec* varDec) override;
    void visitIfStmt(LgsIfStmt* ifStmt) override;
    void visitPatternMatch(const LgsPatternMatch* patternMatching) override;
    void visitBoolPatternMatching(const LgsPatternMatch* patternMatching) const override;
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
    void visitStaticArray(const LgsArrayExpr* array);
    void visitDynamicArray(const LgsArrayExpr* array);
    void visitHashMap(LgsHashMap* hashMap) override;
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr) override;
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr) override;
    void visitVariable(LgsVariable* variable) override;
    void visitFuncCall(LgsFuncCall* funcCall) override;
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitAnonymousFunc(LgsFuncCall* funcCall, LgsFuncType* funcType) override;
    void visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType) override;
    void visitSelection(LgsSelection* selection) override;
    void visitInnerSelections(const LgsSelection* selection) override;
    void visitFieldSelection(const LgsExpr* parentExpr, LgsVariable* childField) override;
    void visitFirstSelection(LgsExpr* firstExpr) override;
    void visitInstance(LgsInstance* instance) override;
    void visitIterIndex(LgsIterIndex* iterIndex) override;
    void visitSlice(LgsIterIndex* iterIndex);
    void visitGroup(LgsGroup* group) const;

    void setBinaryExprType(LgsBinaryExpr* binaryExpr);
    bool setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable);
    void setZeroField(LgsField* field) const;
    bool setLoopVars(LgsForeachLoop* foreachLoop, LgsUnaryExpr* iterExpr, const LgsIterable* iterable);
    void validateExprType(LgsExpr* expr, LgsType* type);
    void validateFuncControlFlow(const LgsFunc* func);
    void validateMethodVisibility(const LgsFuncCall* methodCall);

    LgsSymbol* getSymbol(const string& name, const Location* location);
    void addLocalSymbol(const string& name, const LgsSymbol& newSymbol);
    void resolveFuncCall(LgsFuncCall* funcCall);
    bool resolveMethodCall(LgsFuncCall* methodCall, const LgsType* parentType);
    LgsType* resolveType(LgsType* type);
    void resolveIterable(LgsIterable* iterable);
    void resolveFuncTypes(LgsFuncType* funcType);
    void resolveObjTypes(LgsObject* obj);
    void resolveGroupTypes(LgsGroup* group);
    static void reprocessFuncs(const vector<LgsFile*>& files);
    string getFuncsAsStr(const vector<LgsFunc*>& funcs) const;
    ~SemaAnalyser() override = default;
};


