#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H
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

    void createIRStmt(CodegenMetadata* metadata) override;
    void initIRLoop(CodegenMetadata* metadata);
    void setLoopIRCondition(CodegenMetadata* metadata);
    void exitIRLoop(CodegenMetadata* metadata) const;
    virtual Value* loopStart(CodegenMetadata* metadata) = 0;
    virtual Value* loopEnd(CodegenMetadata* metadata) = 0;
    virtual void setIRIterable(CodegenMetadata* metadata) = 0;
    virtual void setIRLoopVars(CodegenMetadata* metadata) = 0;
    ~LgsForLoop() override;
};

#endif // LOGOSLOOP_H
