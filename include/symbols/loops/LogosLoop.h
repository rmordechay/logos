#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H
#include "stmts/LgsStmt.h"

class LgsVariable;
class LgsStmtBlock;
class LgsExpr;
class LgsLoopVar;

#define BB_LOOP_CONDITION "loop_condition"
#define BB_LOOP_BODY "loop_body"
#define BB_LOOP_END "loop_end"

class LgsLoop : public LgsStmt {
public:
    void iterationLoop(CodeGenMetadata* metadata) const;
    ~LgsLoop() override = default;
};


#endif // LOGOSLOOP_H
