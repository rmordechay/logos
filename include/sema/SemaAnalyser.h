#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include <mutex>
#include "LogosStack.h"
#include "unary/LogosMethodCall.h"

#include "unary/LogosUnaryExpr.h"
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
    LogosFile* file;
    LogosStack logosStack;
    bool successful = true;

    explicit SemaAnalyser(LogosFile* logosFile) : file(logosFile) {}
    void visitLogosFile();
    void visitMainFile(const LogosMainFile* mainFile);
    void visitObjectFile(const LogosObjectFile* objectFile);
    void visitObject(const LogosObject* object);
    static void visitField(LogosField* field);
    void visitMethodImpl(const LogosMethodImpl* method);
    void visitMainFunc(const LogosFuncImpl* mainFunc);
    void visitFuncImpl(const LogosFuncImpl* func);
    static void visitParam(LogosParam* param);
    void visitStmt(LogosStmt* stmt);
    void visitStmtBlock(const LogosStmtBlock* stmtBlock);
    static void visitAssignment(const LogosAssignment* assignment);
    void visitVarDec(LogosVarDec* varDec);
    void visitIfStmt(const LogosIf* ifStmt);
    void visitLoopStmt(LogosLoop* loopStmt);
    void visitRangeLoop(const LogosRangeLoop* rangeLoop);
    void visitForeachLoop(LogosForeachLoop* foreachLoop);
    static void visitReturnStmt(LogosReturn* returnStmt);
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
    static void visitConstant(const LogosConstant* constant);

    void setFuncCallType(LogosFuncCall* funcCall);
    void setMethodCallType(LogosMethodCall* methodCall);
    void setLoopVarType(const LogosForeachLoop* foreachLoop);
    static void setArrayType(LogosArray* array);
    static void setBinaryExprType(LogosBinaryExpr* binaryExpr);
    void setForLoopIterable(LogosForeachLoop* foreachLoop, const LogosVariable* variable);
    void setForLoopIterable(LogosForeachLoop* foreachLoop);

    void resolveFirstSelection(const LogosSelection* selection, LogosVariable* variable);
    void resolveFirstSelection(const LogosSelection* selection, LogosFuncCall* funcCall);
    void resolveInnerSelection(const LogosSelection* selection, int nextIndex, const LogosInstance* instance);
    static void resolveInnerSelection(const LogosSelection* selection, int i, const LogosMethodCall* methodCall);
    static void resolveInnerSelection(const LogosSelection* selection, int i, LogosField* field);
    static void resolveInnerSelection(const LogosSelection* selection, int i, LogosFuncImpl* funcImpl);

    void checkTypesMatch(const LogosType* first, const LogosType* second, const LogosValue* value);
    void setUnsuccessful();

    void printError(int code, const vector<string>& args = {});
    void printError(int code, const LogosValue* value, const vector<string>& args = {});
    LogosSymbol* getSymbol(const string& name, const LogosValue* value);
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
