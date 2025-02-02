#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H

#include "application/ThreadPool.h"
#include "exprs/LogosConstructor.h"
#include "exprs/LogosFuncCall.h"
#include "exprs/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "object/LogosObject.h"
#include "stmts/LogosIfStmt.h"


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
    void visitStmtList(const vector<LogosStmt*>& stmts);
    void visitVarDec(LogosVarDec* varDec);
    void visitIfStmt(const LogosIfStmt* ifStmt);
    void visitExpr(const LogosExpr* expr);
    void visitUnaryExpr(const LogosUnaryExpr* unaryExpr);
    void visitConstructor(const LogosConstructor* constructorExpr);
    void visitFuncCall(const LogosFuncCall* funcCallExpr);
    void visitConstant(const LogosUnaryExpr* unaryExpr);
    LogosType* inferType(const LogosExpr* expr);
    void setUnsuccessful();
    template <class ... Args>
    void printError(int errCode, Position *position, Args&&... args);
    ~SemaAnalyser() = default;
};


#endif //SEMAANALYSER_H
