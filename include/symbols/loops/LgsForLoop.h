#pragma once
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsStmt.h"

class LgsVariable;
class LgsStmtBlock;
class LgsExpr;

#define LOGOS_LOOP_CONDITION "loop_condition"
#define LOGOS_LOOP_BODY "loop_body"
#define LOGOS_LOOP_EXIT "loop_exit"

class LgsForLoop : public LgsStmt {
public:
    AllocaInst* iPtr = nullptr;
    vector<LgsVarDec*> loopVars;
    LgsStmtBlock* stmtBlock = nullptr;
    BasicBlock* IRCondBlock = nullptr;
    BasicBlock* IRBodyBlock = nullptr;
    BasicBlock* IRExitBlock = nullptr;

    void createIRStmt(LgsModule* runtime) override;
    virtual Value* loopStart(LgsModule* runtime) = 0;
    virtual Value* loopEnd(LgsModule* runtime) = 0;
    virtual void initIRLoop(LgsModule* runtime) = 0;
    virtual void exitIRLoop(LgsModule* runtime) const = 0;
    ~LgsForLoop() override;
};


