#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "LgsAnalyser.h"
#include "LgsStack.h"
#include "unary/LogosUnaryExpr.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "types/LgsObject.h"
#include "stmts/LgsReturn.h"
#include <loops/LgsForeachLoop.h>
#include <loops/LgsRangeLoop.h>


class LgsVarDec;
struct LgsSymbol;
class LgsInstance;
class LgsArrayIndex;
class LgsSelection;
class LgsFuncCall;
class LgsBinaryExpr;
class LgsArray;
class LgsIf;
class LgsAssignment;
class LgsLoop;

class SemaAnalyser final : public LgsAnalyser {
public:
    LgsStack logosStack;
    LgsFile* file = nullptr;

    explicit SemaAnalyser(LgsFile* logosFile) : file(logosFile) {}
    void analyse();
    void visitMainFile(const LgsMainFile* mainFile);
    void visitObjectFile(const LgsObjectFile* objectFile);
    void visitObject(LgsObject* obj);
    void visitField(const LgsField* field);
    void visitMethodImpl(LgsMethodImpl* method, LgsObject* obj);
    void visitMainFunc(const LgsFuncImpl* mainFunc);
    void visitFuncImpl(const LgsFuncImpl* func);
    void visitParam(LgsParam* param);
    void visitStmt(LgsStmt* stmt);
    void visitStmtBlock(const LgsStmtBlock* stmtBlock);
    void visitAssignment(const LgsAssignment* assignment);
    void visitVarDec(LgsVarDec* varDec);
    void visitIfStmt(const LgsIf* ifStmt);
    void visitLoopStmt(LgsLoop* loopStmt);
    void visitRangeLoop(const LgsRangeLoop* rangeLoop);
    void visitForeachLoop(LgsForeachLoop* foreachLoop);
    void visitReturnStmt(const LgsReturn* returnStmt);
    void visitExpr(LgsExpr* expr);
    void visitArray(LgsArray* array);
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitVariable(LgsVariable* variable);
    void resolveSelectionVariable(LgsVariable* variable);
    void visitFuncCall(LgsFuncCall* funcCall);
    void setVariableType(LgsVariable* variable);
    void visitSelection(LgsSelection* selection);
    void visitInstance(LgsInstance* instance);
    void visitArrayIndex(LgsArrayIndex* arrayIndex);
    void visitConstant(const LgsConst* constant) const;

    void setFuncCallType(LgsFuncCall* funcCall);
    void setLoopVar(const LgsForeachLoop* foreachLoop);
    void setArrayType(LgsArray* array) const;
    void setBinaryExprType(LgsBinaryExpr* binaryExpr) const;
    void setForLoopIterable(LgsForeachLoop* foreachLoop, const LgsVariable* variable);
    void setForLoopIterable(LgsForeachLoop* foreachLoop);

    bool checkExprType(const LgsExpr* expr, const LgsType* otherType);
    Location* getSymbolPosition(const LgsSymbol* s) const;
    void printError(LgsErrCode code, const Location* location, const vector<string>& args);
    LgsSymbol* getSymbol(const string& name, const LgsValue* value);
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
