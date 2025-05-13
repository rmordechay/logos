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
    BasicBlock* loopCondBlock = nullptr;
    BasicBlock* loopBodyBlock = nullptr;
    BasicBlock* loopExitBlock = nullptr;
    Value* iPtr = nullptr;
    Value* iValue = nullptr;

    void createIRStmt(CodeGenMetadata* metadata) override;
    void initIRLoop(CodeGenMetadata* metadata);
    void setLoopIRCondition(CodeGenMetadata* metadata);
    void exitIRLoop(CodeGenMetadata* metadata) const;
    virtual Value* loopStart(CodeGenMetadata* metadata) = 0;
    virtual Value* loopEnd(CodeGenMetadata* metadata) = 0;
    virtual void setIRLoopVariable(CodeGenMetadata* metadata) = 0;
    ~LgsLoop() override;
};

#endif // LOGOSLOOP_H
