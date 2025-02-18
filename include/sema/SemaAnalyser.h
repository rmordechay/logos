#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H

#include "LogosStack.h"

#include "exprs/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "object/LogosObject.h"


class LogosIf;
class LogosFieldDef;
class LogosLoop;

class SemaAnalyser {
public:
    mutex mtx;
    LogosStack logosStack;
    bool successful = true;

    void visitLogosFile(LogosFile* file);
    void visitMainFile(const LogosMainFile* mainFile);
    void visitObjectFile(const LogosObjectFile* objectFile);
    void visitObject(const LogosObject* object);
    void visitField(LogosField* field);
    void visitMainFunc(const LogosFuncImpl* mainFunc, const std::string& path);
    void visitUserFunc(const LogosFuncImpl* func);
    void visitStmt(LogosStmt* stmt);
    void visitStmtBlock(LogosStmtBlock* stmtBlock);
    void visitFieldDef(const LogosFieldDef* fieldDef);
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
    bool checkErr100(const LogosFuncImpl* mainFunc);
    void setUnsuccessful();
    void resolveSelection(LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr);
    LogosType* inferSelectionType(const LogosSelection* selection);
    template <class ... Args>
    void printError(int errCode, Position *position, Args&&... args);
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
