#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H

#include "stmts/LogosStmt.h"


class LogosStmtBlock;
class LogosExpr;

class LogosLoop final : public LogosStmt {
public:
    LogosVariable* loopVar = nullptr;
    LogosExpr* iterable = nullptr;
    LogosStmtBlock* stmtBlock = nullptr;

    LogosLoop(LogosVariable* loopVar, LogosExpr* iterable, LogosStmtBlock* stmtBlock) : loopVar(loopVar), iterable(iterable), stmtBlock(stmtBlock) {}

    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosLoop() override = default;
};


#endif //LOGOSLOOP_H
