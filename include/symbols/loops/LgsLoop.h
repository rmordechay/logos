#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H
#include "stmts/LgsStmt.h"

class LgsVariable;
class LgsStmtBlock;
class LgsExpr;

#define BB_LOOP_CONDITION "loop_condition"
#define BB_LOOP_BODY "loop_body"
#define BB_LOOP_EXIT "loop_exit"

class LgsLoop : public LgsStmt {
public:
    vector<LgsVarDec*> loopVars;
    LgsStmtBlock* stmtBlock = nullptr;
    BasicBlock* loopCondition = nullptr;
    BasicBlock* loopBody = nullptr;
    BasicBlock* loopExit = nullptr;
    Value* iPtr = nullptr;
    Value* iValue = nullptr;

    LgsLoop(const vector<LgsVarDec*>& loopVars, LgsStmtBlock* stmtBlock) : loopVars(loopVars), stmtBlock(stmtBlock) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void initIRLoop(CodeGenMetadata* metadata);
    void setLoopIRCondition(CodeGenMetadata* metadata);
    void exitIRLoop(CodeGenMetadata* metadata) const;
    virtual int loopStart() = 0;
    virtual int loopEnd() = 0;
    virtual void setIRBody(CodeGenMetadata* metadata) = 0;
    ~LgsLoop() override = default;
};

#endif // LOGOSLOOP_H
