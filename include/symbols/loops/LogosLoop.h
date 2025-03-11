#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H
#include "stmts/LogosStmt.h"

class LogosVariable;
class LogosStmtBlock;
class LogosExpr;
class LogosLoopVar;

#define BB_LOOP_CONDITION "loop_condition"
#define BB_LOOP_BODY "loop_body"
#define BB_LOOP_END "loop_end"

class LogosLoop : public LogosStmt {
public:
    void iterationLoop(CodeGenMetadata* metadata) const;
    ~LogosLoop() override = default;
};


#endif // LOGOSLOOP_H
