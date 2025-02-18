#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H

#include "stmts/LogosStmt.h"


class LogosVariable;
class LogosStmtBlock;
class LogosExpr;

enum LogosLoopType {
    RANGE_LOOP,
    FOREACH_LOOP,
    INFINITE_LOOP,
};

class LogosLoop final : public LogosStmt
{
public:
    LogosLoopType loopType;
    LogosVariable* loopVar = nullptr;
    LogosExpr* iterable = nullptr;
    LogosStmtBlock* stmtBlock = nullptr;

    LogosLoop(const LogosLoopType loopType, LogosVariable* loopVar, LogosExpr* iterable, LogosStmtBlock* stmtBlock) : loopType(loopType), loopVar(loopVar), iterable(iterable), stmtBlock(stmtBlock) {}
    LogosLoop(const LogosLoopType loopType, LogosVariable* loopVar, LogosStmtBlock* stmtBlock) : LogosLoop(loopType, loopVar, nullptr, stmtBlock) {}
    LogosLoop(const LogosLoopType loopType, LogosStmtBlock* stmtBlock) : LogosLoop(loopType, nullptr, stmtBlock) {}

    void iterationLoop(CodeGenMetadata* metadata) const;
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosLoop() override = default;
};


#endif //LOGOSLOOP_H
