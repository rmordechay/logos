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

    void createIRStmt(LgsCodeGen* codeGen) override;
    virtual Value* loopStart(LgsCodeGen* codeGen) = 0;
    virtual Value* loopEnd(LgsCodeGen* codeGen) = 0;
    virtual void initIRLoop(LgsCodeGen* codeGen) = 0;
    virtual void IRLoopPrologue(LgsCodeGen* codeGen) const = 0;
    ~LgsForLoop() override;
};


