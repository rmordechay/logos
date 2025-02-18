#ifndef SEMAFILE_H
#define SEMAFILE_H
#include <mutex>

#include "LogosStack.h"
#include "exprs/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "stmts/LogosFieldDef.h"
#include "stmts/LogosIf.h"
#include "stmts/LogosVarDec.h"
#include <stmts/LogosLoop.h>

class SemaFileAnalyser {
public:
    mutex mtx;
    LogosStack logosStack;
    bool successful = true;
    LogosMainFile* mainFile = nullptr;

    explicit SemaFileAnalyser(const LogosStack& logosStack) : logosStack(logosStack) {}

    void visitMainFile(const LogosMainFile* mainFile);
    void visitObjectFile(const LogosObjectFile* objectFile);
    void visitObject(const LogosObject* object);
    void visitField(LogosField* field);
    void visitMainFunc(const LogosUserFunc* mainFunc, const std::string& path);
    void visitUserFunc(const LogosUserFunc* func);
    void visitStmt(LogosStmt* stmt);
    void visitStmtBlock(LogosStmtBlock* stmtBlock);
    void visitFieldDef(const LogosFieldDefinition* fieldDef);
    void visitVarDec(LogosVarDec* varDec);
    void visitIfStmt(const LogosIf* ifStmt);
    void visitLoopStmt(const LogosLoop* loopStmt);
    void visitExpr(LogosExpr* expr);
    void visitArray(const LogosArray* array);
    void visitUnaryExpr(LogosUnaryExpr* unaryExpr);
    void visitBinaryExpr(const LogosBinaryExpr* binaryExpr);
    void visitFuncCall(const LogosFuncCall* funcCallExpr);
    void visitVariable(const LogosVariable* variable);
    void visitSelection(const LogosSelection* selection);
    void visitInstance(LogosInstance* instance);
    void visitArrayIndex(const LogosArrayIndex* arrayIndex);
    void visitConstant(const LogosConstant* constant);
    bool checkErr100(const LogosUserFunc* mainFunc);
    void setUnsuccessful();
    void resolveSelection(LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr);
    LogosType* inferSelectionType(const LogosSelection* selection);
    template <class ... Args>
    void printError(int errCode, Position *position, Args&&... args);
    ~SemaFileAnalyser();

};

#endif //SEMAFILE_H
