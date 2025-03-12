#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "LogosAnalyser.h"
#include "LogosStack.h"
#include "unary/LogosMethodCall.h"
#include "unary/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "types/LogosObject.h"
#include "stmts/LogosReturn.h"
#include <loops/LogosForeachLoop.h>
#include <loops/LogosRangeLoop.h>


class LogosIf;
class LogosAssignment;
class LogosLoop;

class SemaAnalyser final : public LogosAnalyser {
public:
    LogosStack logosStack;
    LogosFile* file = nullptr;

    explicit SemaAnalyser(LogosFile* logosFile) : file(logosFile) {}
    void analyse();
    void visitMainFile(const LogosMainFile* mainFile);
    void visitObjectFile(const LogosObjectFile* objectFile);
    void visitObject(LogosObject* obj);
    void visitField(LogosField* field);
    void visitMethodImpl(LogosMethodImpl* method, LogosObject* obj);
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
    void resolveSelectionVariable(LogosVariable* variable);
    void visitFuncCall(LogosFuncCall* funcCall);
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

    bool matchTypes(const LogosType* first, const LogosType* second, const LogosValue* value);
    void printError(LogosErrCode code, const LogosValue* value, const vector<string>& args = {});
    LogosSymbol* getSymbol(const string& name, const LogosValue* value);
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
