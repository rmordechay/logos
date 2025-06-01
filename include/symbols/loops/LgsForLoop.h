#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H
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
    BasicBlock* loopCondBlock = nullptr;
    BasicBlock* loopBodyBlock = nullptr;
    BasicBlock* loopExitBlock = nullptr;

    void createIRStmt(Module* module) override;
    void initIRLoop(Module* module);
    void setLoopIRCondition(Module* module);
    void exitIRLoop(Module* module) const;
    virtual Value* loopStart(Module* module) = 0;
    virtual Value* loopEnd(Module* module) = 0;
    virtual void setIRIterable(Module* module) = 0;
    virtual void setIRLoopVars(Module* module) = 0;
    ~LgsForLoop() override;
};

#endif // LOGOSLOOP_H
