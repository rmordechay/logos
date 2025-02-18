#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H

#include "LogosStack.h"
#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "exprs/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "object/LogosObject.h"
#include "stmts/LogosFieldDef.h"
#include "stmts/LogosIf.h"
#include "stmts/LogosVarDec.h"


class LogosLoop;

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
    ~SemaAnalyser();
};


#endif //SEMAANALYSER_H
