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
    LgsVarDec* loopVar = nullptr;
    LgsStmtBlock* stmtBlock = nullptr;

    LgsLoop(LgsVarDec* loopVar, LgsStmtBlock* stmtBlock) : loopVar(loopVar), stmtBlock(stmtBlock) {}
    void iterationLoop(CodeGenMetadata* metadata) const;
    ~LgsLoop() override = default;
};


#endif // LOGOSLOOP_H
