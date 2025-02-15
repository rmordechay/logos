#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H

#include "LogosStack.h"
#include "application/ThreadPool.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstructor.h"
#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "exprs/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "object/LogosObject.h"
#include "stmts/LogosFieldDef.h"
#include "stmts/LogosIf.h"


class SemaAnalyser {
public:
    bool successful = true;
    LogosMainFile* mainFile = nullptr;
    map<string, LogosFile*> files;
    LogosStack theStack;
    mutex mtx;

    bool analyse();
    void collectGlobals();
    void visitLogosFile(LogosFile* file);
    void visitMainFile(const LogosMainFile* mainFile);
    void visitObjectFile(const LogosObjectFile* objectFile);
    void visitObject(const LogosObject* object);
    void visitMainFunc(const LogosUserFunc* mainFunc, const string& path);
    void visitUserFunc(const LogosUserFunc* func);
    void visitStmt(LogosStmt* stmt);
    void visitStmtBlock(LogosStmtBlock* stmtBlock);
    void visitField(LogosField* field);
    void visitFieldDef(const LogosFieldDef* fieldDef);
    void visitVarDec(LogosVarDec* varDec);
    void visitIfStmt(const LogosIf* ifStmt);
    void visitExpr(LogosExpr* expr);
    void visitUnaryExpr(LogosUnaryExpr* unaryExpr);
    void visitBinaryExpr(const LogosBinaryExpr* binaryExpr);
    void visitSelection(const LogosSelection* selection);
    void visitConstructor(LogosConstructor* constructorExpr);
    void visitFuncCall(const LogosFuncCall* funcCallExpr);
    void visitConstant(const LogosUnaryExpr* unaryExpr);
    void setUnsuccessful();
    void resolveSelection(LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr);
    LogosType* inferSelectionType(const LogosSelection* selection);
    void checkTypes(LogosVarDec* varDec, LogosType* type);
    template <class ... Args>
    void printError(int errCode, Position *position, Args&&... args);
    ~SemaAnalyser();
};


#endif //SEMAANALYSER_H
