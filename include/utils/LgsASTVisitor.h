#pragma once
#include "../logos/LgsStack.h"
#include "files/LgsInterfaceFile.h"

class LgsFuncType;
class LgsArray;
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

class LgsASTVisitor {
public:
    LgsFile* file = nullptr;

    explicit LgsASTVisitor(LgsFile* file) : file(file) {}
    virtual void analyse() = 0;
    virtual void visitMainFile(LgsMainFile* mainFile) = 0;
    virtual void visitObject(LgsObject* obj) = 0;
    virtual void visitInterface(LgsInterface* interface) = 0;
    virtual void visitField(LgsField* field) = 0;
    virtual void visitFunc(LgsFunc* func) = 0;
    virtual void visitParam(LgsParam* param) = 0;
    virtual void visitStmt(LgsStmt* stmt) = 0;
    virtual void visitStmtBlock(LgsStmtBlock* stmtBlock) = 0;
    virtual void visitAssignment(LgsAssignment* assignment) = 0;
    virtual void visitVarDec(LgsVarDec* varDec) = 0;
    virtual void visitIfStmt(LgsIfStmt* ifStmt) = 0;
    virtual void visitPatternMatch(const LgsPatternMatch* patternMatching) = 0;
    virtual void visitBoolPatternMatching(const LgsPatternMatch* patternMatching) = 0;
    virtual void visitLoopStmt(LgsForLoop* loopStmt) = 0;
    virtual void visitRangeLoop(const LgsRangeLoop* rangeLoop) = 0;
    virtual void visitForeachLoop(LgsForeachLoop* foreachLoop) = 0;
    virtual void visitReturnStmt(const LgsReturn* returnStmt) = 0;
    virtual void visitBreakStmt(const LgsBreakStmt* breakStmt) = 0;
    virtual void visitContinueStmt(const LgsContinueStmt* continueStmt) = 0;
    virtual void visitEnum(const LgsEnum* lgsEnum) const = 0;
    virtual void visitExpr(LgsExpr* expr) = 0;
    virtual void visitCast(LgsCast* castExpr) = 0;
    virtual void visitArrayExpr(LgsArrayExpr* array) = 0;
    virtual void visitHashMap(LgsHashMap* hashMap) = 0;
    virtual void visitUnaryExpr(LgsUnaryExpr* unaryExpr) = 0;
    virtual void visitBinaryExpr(LgsBinaryExpr* binaryExpr) = 0;
    virtual void visitVariable(LgsVariable* variable) = 0;
    virtual void visitFuncCall(LgsFuncCall* funcCall) = 0;
    virtual void visitAnonymousFunc(LgsFuncCall* funcCall, LgsFuncType* funcType) = 0;
    virtual void visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType) = 0;
    virtual void visitSelection(LgsSelection* selection) = 0;
    virtual void visitInnerSelections(const LgsSelection* selection) = 0;
    virtual void visitFieldSelection(const LgsExpr* parentExpr, LgsVariable* childField) = 0;
    virtual void visitFirstSelection(LgsExpr* firstExpr) = 0;
    virtual void visitInstance(LgsInstance* instance) = 0;
    virtual void visitIterIndex(LgsIterIndex* iterIndex) = 0;
    virtual void visitSlice(LgsIterIndex* iterIndex) = 0;
    virtual void visitGroup(LgsGroup* group) const = 0;
    virtual ~LgsASTVisitor() = default;
};
