#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H
#include "stmts/LogosStmt.h"

class LogosVariable;
class LogosStmtBlock;
class LogosExpr;
class LogosLoopVar;

class LogosLoop : public LogosStmt {
public:
    void iterationLoop(CodeGenMetadata* metadata) const;
    ~LogosLoop() override = default;
};


#endif // LOGOSLOOP_H
