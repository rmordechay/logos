#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "LgsErrorHandler.h"
#include "LgsStack.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "files/LgsMainFile.h"
#include "stmts/LgsBreakStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "stmts/LgsReturn.h"
#include <loops/LgsForeachLoop.h>
#include <loops/LgsRangeLoop.h>


class LgsCast;
class LgsVarDec;
struct LgsSymbol;
class LgsInstance;
class LgsArrayIndex;
class LgsSelection;
class LgsFuncCall;
class LgsBinaryExpr;
class LgsArray;
class LgsIfStmt;
class LgsAssignment;
class LgsLoop;

class SemaAnalyser final {
public:
    LgsStack lgsStack;
    LgsFile* file = nullptr;
    LgsErrorHandler errHandler;

    explicit SemaAnalyser(LgsFile* file) : file(file) {
        errHandler.filePath = file->absPath;
    }
    void analyse();
    void visitMainFile(LgsMainFile* mainFile);
    void visitObject(LgsObject* obj);
    void visitInterface(LgsInterface* interface);
    void visitObjectImplements(LgsObject* obj);
    void visitField(const LgsField* field);
    void visitFunc(LgsFunc* func);
    void visitFuncSignature(LgsFuncSignature* funcSignature);
    void validateFuncControlFlow(const LgsFunc* func);
    void visitParam(LgsParam* param);
    void visitStmt(LgsStmt* stmt);
    void visitStmtBlock(LgsStmtBlock* stmtBlock);
    void visitAssignment(const LgsAssignment* assignment);
    void visitVarDec(LgsVarDec* varDec);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitPatternMatch(const LgsPatternMatch* patternMatching);
    void visitBoolPatternMatching(const LgsPatternMatch* patternMatching) const;
    void visitLoopStmt(LgsLoop* loopStmt);
    void visitRangeLoop(const LgsRangeLoop* rangeLoop);
    void visitForeachLoop(const LgsForeachLoop* foreachLoop);
    void visitReturnStmt(const LgsReturn* returnStmt);
    void visitBreakStmt(LgsBreakStmt* breakStmt) const;
    void visitEnum(const LgsEnum* lgsEnum) const;
    void visitExpr(LgsExpr* expr);
    void visitCast(LgsCast* castExpr);
    void visitArray(const LgsArray* array);
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitVariable(LgsVariable* variable);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType);
    void visitSelection(LgsSelection* selection);
    void visitInnerSelections(const LgsSelection* selection);
    void visitFieldCall(const LgsExpr* parentExpr, LgsVariable* childField);
    void visitFirstSelection(LgsExpr* firstExpr);
    void visitInstance(LgsInstance* instance);
    void visitArrayIndex(LgsArrayIndex* arrayIndex);

    void setExprType(LgsExpr* expr, LgsType* type);
    void setBinaryExprType(LgsBinaryExpr* binaryExpr);
    bool setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable);

    bool resolveFuncCall(const vector<LgsFunc*>& overloads, LgsFuncCall* funcCall);
    LgsFunc* resolveFuncCallWithDefaultParams(LgsFunc* func, const LgsFuncCall* funcCall) const;
    void checkDuplicateFuncs(const vector<LgsFuncImpl*>& overloads);
    bool validateExprType(LgsExpr* expr, LgsType* type);
    string getOverloadsAsStr(const vector<LgsFunc*>& overloads) const;

    LgsSymbol* getSymbol(const string& name, const LgsValue* value);
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
