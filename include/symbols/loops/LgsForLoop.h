#pragma once
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsStmt.h"

class LgsVariable;
class LgsStmtsBlock;
class LgsExpr;

class LgsForLoop : public LgsStmt {
public:
    vector<LgsVarDec*> loopVars;
    AllocaInst* iPtr = nullptr;
    LgsStmtsBlock* stmtBlock = nullptr;
    BasicBlock* IRCondBlock = nullptr;
    BasicBlock* IRBodyBlock = nullptr;
    BasicBlock* IRExitBlock = nullptr;

    void createIRStmt(LgsModule* module) override;
    virtual Value* loopStart(LgsModule* module) = 0;
    virtual Value* loopEnd(LgsModule* module) = 0;
    virtual void initIRLoop(LgsModule* module) = 0;
    virtual void exitIRLoop(LgsModule* module) const = 0;
    ~LgsForLoop() override;
};


