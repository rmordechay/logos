#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include <mutex>
#include "LogosStack.h"
#include "exprs/LogosMethodCall.h"

#include "exprs/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "object/LogosObject.h"
#include "stmts/LogosReturn.h"

#include <loops/LogosForeachLoop.h>
#include <loops/LogosRangeLoop.h>


class LogosIf;
class LogosAssignment;
class LogosLoop;

class SemaAnalyser {
public:
    std::mutex mtx;
    LogosStack logosStack;
    bool successful = true;

    void visitLogosFile(LogosFile* file);
    void visitMainFile(const LogosMainFile* mainFile);
    void visitObjectFile(const LogosObjectFile* objectFile);
    void visitObject(const LogosObject* object);
    void visitField(LogosField* field);
    void visitMethodImpl(const LogosMethodImpl* method);
    void visitMainFunc(const LogosFuncImpl* mainFunc, const std::string& path);
    void visitFuncImpl(const LogosFuncImpl* func);
    void visitParam(LogosParam* param);
    void visitStmt(LogosStmt* stmt);
    void visitStmtBlock(const LogosStmtBlock* stmtBlock);
    void visitAssignment(const LogosAssignment* assignment);
    void visitVarDec(LogosVarDec* varDec);
    void visitIfStmt(const LogosIf* ifStmt);
    void visitLoopStmt(LogosLoop* loopStmt);
    void visitRangeLoop(const LogosRangeLoop* rangeLoop);
    void visitForeachLoop(LogosForeachLoop* foreachLoop);
    void visitReturnStmt(LogosReturn* returnStmt);
    void visitExpr(LogosExpr* expr);
    void visitArray(LogosArray* array);
    void visitUnaryExpr(LogosUnaryExpr* unaryExpr);
    void visitBinaryExpr(LogosBinaryExpr* binaryExpr);
    void visitVariable(LogosVariable* variable);
    void visitFuncCall(LogosFuncCall* funcCall);
    void visitMethodCall(LogosMethodCall* methodCall);
    void setVariableType(LogosVariable* variable);
    void visitSelection(LogosSelection* selection);
    void visitInstance(LogosInstance* instance);
    void visitArrayIndex(LogosArrayIndex* arrayIndex);
    void setFuncCallType(LogosFuncCall* funcCall);
    void setMethodCallType(LogosMethodCall* methodCall);
    void visitConstant(const LogosConstant* constant);
    void setLoopVarType(const LogosForeachLoop* foreachLoop);
    void setArrayType(LogosArray* array);
    void setBinaryExprType(LogosBinaryExpr* binaryExpr);
    void setForLoopIterable(LogosForeachLoop* foreachLoop, const LogosVariable* variable);
    void setForLoopIterable(LogosForeachLoop* foreachLoop);
    void resolveFirstSelection(const LogosSelection* selection, LogosVariable* variable);
    void resolveFirstSelection(const LogosSelection* selection, LogosFuncCall* funcCall);
    void resolveInnerSelection(const LogosSelection* selection, int nextIndex, const LogosInstance* instance);
    void resolveInnerSelection(const LogosSelection* selection, int i, const LogosMethodCall* methodCall);
    void resolveInnerSelection(const LogosSelection* selection, int i, LogosField* field);
    void resolveInnerSelection(const LogosSelection* selection, int i, LogosFuncImpl* funcImpl);
    void checkTypesMatch(const LogosType* first, const LogosType* second, const Position& position);
    void setUnsuccessful();
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
