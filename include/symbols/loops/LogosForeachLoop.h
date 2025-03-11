#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LogosLoop.h"

class LogosIterable;

class LogosForeachLoop final : public LogosLoop {
public:
    LogosLoopVar* loopVar = nullptr;
    LogosExpr* iterableExpr = nullptr;
    LogosIterable* iterable = nullptr;
    LogosStmtBlock* stmtBlock = nullptr;

    LogosForeachLoop(LogosLoopVar* loopVar, LogosExpr* iterableExpr, LogosStmtBlock* stmtBlock) : loopVar(loopVar), iterableExpr(iterableExpr), stmtBlock(stmtBlock) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LogosForeachLoop() override;
};


#endif //LOGOSFOREACHLOOP_H
