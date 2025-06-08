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
    void initIRLoop(LgsRuntime* runtime);
    void setLoopIRCondition(LgsRuntime* runtime);
    void exitIRLoop(LgsRuntime* runtime) const;
    virtual Value* loopStart(LgsRuntime* runtime) = 0;
    virtual Value* loopEnd(LgsRuntime* runtime) = 0;
    virtual void setIRIterable(LgsRuntime* runtime) = 0;
    virtual void setIRLoopVars(LgsRuntime* runtime) = 0;
    ~LgsForLoop() override;
};


