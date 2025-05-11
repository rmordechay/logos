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
class LgsDArray;
class LgsIfStmt;
class LgsAssignment;
class LgsLoop;

inline std::mutex mtx;

LgsType* resolveType(LgsType* type, LgsErrHandler* errorHandler);
void resolveFuncTypes(LgsFuncType* signature, LgsErrHandler* errHandler);
void resolveGlobalTypes(const vector<LgsFile*>& files, LgsErrHandler* errHandler);
void resolveObjMemberTypes(LgsObject* const& obj, LgsErrHandler* errHandler);
void resolveObjectImplements(LgsObject* obj, LgsErrHandler* errHandler);
string getOverloadsAsStr(const vector<LgsMethodImpl*>& overloads);
string getOverloadsAsStr(const vector<LgsFunc*>& overloads);

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
    void visitInterface(LgsInterface* interface);
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
    void visitDArray(LgsDArray* array);
    void visitSArray(LgsSArray* array);
    void visitHashMap(LgsHashMap* hashMap) const;
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitVariable(LgsVariable* variable);
    void visitFuncCall(LgsFuncCall* funcCall);
    void resolveFuncCall(LgsFuncCall* funcCall);
    void visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType);
    void visitSelection(LgsSelection* selection);
    void visitInnerSelections(const LgsSelection* selection);
    void visitFieldCall(const LgsExpr* parentExpr, LgsVariable* childField);
    void visitFirstSelection(LgsExpr* firstExpr);
    void visitInstance(LgsInstance* instance);
    void visitIterIndex(LgsIterIndex* iterIndex);

    void setExprType(LgsExpr* expr, LgsType* type);
    void setBinaryExprType(LgsBinaryExpr* binaryExpr);
    bool setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable);
    void setIterIndexType(LgsIterIndex* iterIndex) const;

    LgsFunc* resolveMethodCall(const vector<LgsMethodImpl*>& overloads, LgsFuncCall* methodCall, const string& parentName);
    bool resolveFuncCallWithDefaultParams(const LgsFuncType* funcType, const LgsFuncCall* funcCall) const;
    bool isFuncCallEqual(const LgsFuncType* funcType, LgsFuncCall* funcCall) const;
    bool isFuncCallEqual(LgsFunc* func, LgsFuncCall* funcCall) const;
    bool checkExprType(LgsExpr* expr, LgsType* type);
    bool checkSingleIndexBoundaries(LgsIterIndex* iterIndex, LgsExpr* index, size_t upperBound);
    bool checkSliceBoundaries(LgsIterIndex* iterIndex, const LgsIndex* index, size_t upperBound);
    bool checkIndexBoundaries(LgsIterIndex* iterIndex);
    void checkDuplicateFuncs(const vector<LgsFuncImpl*>& overloads);
    void checkMethodVisibility(const LgsFuncCall* methodCall);

    LgsSymbol* getSymbol(const string& name, const LgsValue* value = nullptr);
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
