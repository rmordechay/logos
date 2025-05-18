#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H
#include "stmts/LgsStmt.h"

class LgsVariable;
class LgsStmtBlock;
class LgsExpr;

class LgsLoop : public LgsStmt {
public:
    vector<LgsVarDec*> loopVars;
    LgsStmtBlock* stmtBlock = nullptr;
    BasicBlock* loopCondBlock = nullptr;
    BasicBlock* loopBodyBlock = nullptr;
    BasicBlock* loopExitBlock = nullptr;
    Value* iPtr = nullptr;

    void createIRStmt(CodeGenMetadata* metadata) override;
    void initIRLoop(CodeGenMetadata* metadata);
    void setLoopIRCondition(CodeGenMetadata* metadata);
    void exitIRLoop(CodeGenMetadata* metadata) const;
    virtual Value* loopStart(CodeGenMetadata* metadata) = 0;
    virtual Value* loopEnd(CodeGenMetadata* metadata) = 0;
    virtual void setIRLoopVars(CodeGenMetadata* metadata) = 0;
    ~LgsLoop() override;
};

#endif // LOGOSLOOP_H
