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
    vector<LogosFile*> files;
    mutex mtx;

    bool analyse();
    void visitLogosFile(LogosFile* file);
    void visitMainFile(const LogosMainFile* mainFile);
    void visitObjectFile(const LogosObjectFile* objectFile);
    void visitObject(const LogosObject* object);
    void visitMainFunc(const LogosUserFunc* mainFunc, const string& path);
    void visitFunc(const LogosFunc* func);
    void visitStmt(const LogosStmt* stmt);
    void visitStmtList(const vector<LogosStmt*>& stmts);
    void visitVarDec(const LogosVarDec* varDec);
    void visitIfStmt(const LogosIfStmt* ifStmt);
    void visitExpr(const LogosExpr* expr);
    void visitUnaryExpr(const LogosUnaryExpr* unaryExpr);
    void visitConstructor(const LogosConstructor* constructorExpr);
    void visitFuncCall(const LogosFuncCall* funcCallExpr);
    void visitConstant(const LogosUnaryExpr* unaryExpr);
    void setUnsuccessful();
    void printError(int errCode, Position position);
    void printError(int errCode, const string& path);
    ~SemaAnalyser() = default;
};


#endif //SEMAANALYSER_H
