#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "LogosError.h"

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
    void visitField(LogosField* field);
    void visitMethodImpl(const LogosMethodImpl* method);
    void visitMainFunc(const LogosFuncImpl* mainFunc);
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
    void visitReturnStmt(const LogosReturn* returnStmt);
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
    void visitConstant(const LogosConstant* constant);

    void setFuncCallType(LogosFuncCall* funcCall);
    void setLoopVarType(const LogosForeachLoop* foreachLoop);
    void setArrayType(LogosArray* array);
    void setBinaryExprType(LogosBinaryExpr* binaryExpr);
    void setForLoopIterable(LogosForeachLoop* foreachLoop, const LogosVariable* variable);
    void setForLoopIterable(LogosForeachLoop* foreachLoop);

    void resolveFirstSelection(const LogosSelection* selection, LogosVariable* variable);
    void resolveFirstSelection(const LogosSelection* selection, LogosFuncCall* funcCall);
    void resolveInnerSelection(const LogosSelection* selection, int i, LogosInstance* instance);
    void resolveInnerSelection(const LogosSelection* selection, int i, LogosMethodCall* methodCall);
    void resolveInnerSelection(const LogosSelection* selection, int i, LogosField* field);
    void resolveInnerSelection(const LogosSelection* selection, int i, LogosFuncImpl* funcImpl);

    bool matchTypes(const LogosType* first, const LogosType* second, const LogosValue* value);
    void setUnsuccessful();

    void printError(LogosErrorNo code, const vector<string>& args = {});
    void printError(LogosErrorNo code, const LogosValue* value, const vector<string>& args = {});
    LogosSymbol* getSymbol(const string& name, const LogosValue* value);
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
