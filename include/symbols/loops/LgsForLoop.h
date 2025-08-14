#pragma once
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsStmt.h"
class LgsVariable;
class LgsStmtsBlock;
class LgsExpr;

class LgsForLoop : public LgsStmt {
public:
    std::vector<LgsVarDec*> loopVars;
    AllocaInst* iPtr = nullptr;
    LgsStmtsBlock* stmtsBlock = nullptr;
    BasicBlock* IRCondBlock = nullptr;
    BasicBlock* IRBodyBlock = nullptr;
    BasicBlock* IRExitBlock = nullptr;
    LgsVarDec* isFirst = nullptr;
    LgsVarDec* isLast = nullptr;

    void createIRStmt(LgsCodeGen* codeGen) override;
    void initIndex(LgsCodeGen* codeGen);
    Value* loadIndex(LgsCodeGen* codeGen) const;
    void incIndex(LgsCodeGen* codeGen) const;
    virtual void setBlocks(LgsCodeGen* codeGen);
    virtual void incAndJumpToCond(LgsCodeGen* codeGen) const;
    virtual void createIRLoop(LgsCodeGen* codeGen) = 0;
    ~LgsForLoop() override;
};


