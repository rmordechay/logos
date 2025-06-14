#pragma once
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsStmt.h"

class LgsVariable;
class LgsStmtBlock;
class LgsExpr;

class LgsForLoop : public LgsStmt {
public:
    AllocaInst* iPtr = nullptr;
    vector<LgsVarDec*> loopVars;
    LgsStmtBlock* stmtBlock = nullptr;
    BasicBlock* IRCondBlock = nullptr;
    BasicBlock* IRBodyBlock = nullptr;
    BasicBlock* IRExitBlock = nullptr;

    void createIRStmt(LgsRuntime* runtime) override;
    virtual Value* loopStart(LgsRuntime* runtime) = 0;
    virtual Value* loopEnd(LgsRuntime* runtime) = 0;
    virtual void initIRLoop(LgsRuntime* runtime) = 0;
    virtual void exitIRLoop(LgsRuntime* runtime) const = 0;
    ~LgsForLoop() override;
};


