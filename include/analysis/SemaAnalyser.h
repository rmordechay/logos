#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "LgsErrHandler.h"
#include "LgsStack.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "files/LgsMainFile.h"
#include "stmts/LgsBreakStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "stmts/LgsReturn.h"
#include <loops/LgsForeachLoop.h>
#include <loops/LgsRangeLoop.h>
#include <mutex>

class LogosProject;
class LgsIndex;
class LgsCast;
class LgsVarDec;
struct LgsSymbol;
class LgsInstance;
class LgsIterIndex;
class LgsSelection;
class LgsFuncCall;
class LgsBinaryExpr;
class LgsArrayExpr;
class LgsIfStmt;
class LgsAssignment;
class LgsLoop;

bool resolveGlobalTypes(const vector<LgsFile*>& files);

class SemaAnalyser final {
public:
    LgsStack lgsStack;
    LgsFile* file = nullptr;
    LgsErrHandler errHandler;

    explicit SemaAnalyser(LgsFile* file) : file(file) {
        errHandler.filePath = file->absPath;
    }
    static void analyseFiles(const LogosProject* project, vector<LgsError>& errors);
    void analyse();
    void visitMainFile(LgsMainFile* mainFile);
    void visitObject(LgsObject* obj);
    void visitInterface(LgsInterface* interface) const;
    void visitField(const LgsField* field);
    void visitFunc(LgsFunc* func);
    void visitFuncType(const LgsFuncType* funcType);
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
    void visitBreakStmt(const LgsBreakStmt* breakStmt);
    void visitContinueStmt(const LgsContinueStmt* continueStmt);
    void visitEnum(const LgsEnum* lgsEnum) const;
    void visitExpr(LgsExpr* expr);
    void visitCast(LgsCast* castExpr);
    void visitArrayExpr(LgsArrayExpr* array);
    void visitHashMap(LgsHashMap* hashMap) const;
    void visitStrConst(LgsStrConst* strConst) const;
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitVariable(LgsVariable* variable);
    void visitFuncCall(LgsFuncCall* funcCall);
    void resolveFuncCall(LgsFuncCall* funcCall);
    void visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType);
    void visitSelection(LgsSelection* selection);
    void visitInnerSelections(const LgsSelection* selection);
    void visitFieldSelection(const LgsExpr* parentExpr, LgsVariable* childField);
    void visitFirstSelection(LgsExpr* firstExpr);
    void visitInstance(LgsInstance* instance);
    void visitIterIndex(LgsIterIndex* iterIndex);

    void setBinaryExprType(LgsBinaryExpr* binaryExpr);
    bool setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable);
    void setIterIndexType(LgsIterIndex* iterIndex);

    LgsFunc* resolveMethodCall(const vector<LgsMethodImpl*>& overloads, LgsFuncCall* methodCall, const string& parentName);
    bool isFuncCallEqual(const LgsFuncCall* funcCall, const LgsFuncType* funcType) const;
    bool resolveCallback(LgsFuncCall* funcCall, const LgsFuncType* funcType);
    bool resolveFuncCall(LgsFuncCall* funcCall, LgsFunc* func) const;
    bool validateExprType(const LgsExpr* expr, LgsType* type);
    void checkDuplicateFuncs(const vector<LgsFuncImpl*>& overloads);
    void checkMethodVisibility(const LgsFuncCall* methodCall);

    LgsSymbol* getSymbol(const string& name, const LgsValue* value = nullptr);
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);

    LgsType* resolveType(LgsType* type);
    LgsType* resolveArrayType(LgsArray* array);
    void resolveFuncTypes(LgsFuncType* signature);
    void resolveObjMemberTypes(LgsObject* const& obj);
    void resolveObjectImplements(LgsObject* obj);
    string getOverloadsAsStr(const vector<LgsMethodImpl*>& overloads) const;
    string getOverloadsAsStr(const vector<LgsFunc*>& overloads) const;
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
