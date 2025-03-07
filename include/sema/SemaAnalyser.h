#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include <mutex>
#include "LogosStack.h"

#include "exprs/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "object/LogosObject.h"

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

    static void analyse(const map<string, LogosFile*>& files, const map<string, LogosSymbol>& globalSymbols);
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
    void visitAssignment(const LogosAssignment* fieldDef);
    void visitVarDec(LogosVarDec* varDec);
    void visitIfStmt(const LogosIf* ifStmt);
    void visitLoopStmt(LogosLoop* loopStmt);
    void visitRangeLoop(const LogosRangeLoop* rangeLoop);
    void visitForeachLoop(LogosForeachLoop* foreachLoop);
    void visitExpr(LogosExpr* expr);
    void visitArray(LogosArray* array);
    void visitUnaryExpr(LogosUnaryExpr* unaryExpr);
    void visitBinaryExpr(const LogosBinaryExpr* binaryExpr);
    void visitFuncCall(LogosFuncCall* funcCall);
    void visitVariable(LogosVariable* variable);
    void visitSelection(LogosSelection* selection);
    void visitInstance(LogosInstance* instance);
    void visitArrayIndex(LogosArrayIndex* arrayIndex);
    void visitConstant(const LogosConstant* constant);
    void setUnsuccessful();
    void resolveSelection(LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr);
    LogosType* inferSelectionType(LogosSelection* selection);
    void setArrayType(LogosArray* array);
    void setIterable(LogosForeachLoop* foreachLoop, const LogosVariable* variable);
    void setIterable(LogosForeachLoop* foreachLoop);
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
