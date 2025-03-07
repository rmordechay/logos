#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H
#include "stmts/LogosStmt.h"

class LogosVariable;
class LogosStmtBlock;
class LogosExpr;
class LogosLoopVar;

class LogosLoop : public LogosStmt {
public:
    BasicBlock* const loopCondition = BasicBlock::Create(context, "loop_condition");
    BasicBlock* const loopBody = BasicBlock::Create(context, "loop_body");
    BasicBlock* const loopEnd = BasicBlock::Create(context, "loop_end");

    void iterationLoop(CodeGenMetadata* metadata) const;
    ~LogosLoop() override = default;
};


#endif // LOGOSLOOP_H
