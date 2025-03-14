#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LogosLoop.h"

class LgsIterable;

class LgsForeachLoop final : public LgsLoop {
public:
    LgsLoopVar* loopVar = nullptr;
    LogosExpr* iterableExpr = nullptr;
    LgsIterable* iterable = nullptr;
    LgsStmtBlock* stmtBlock = nullptr;

    LgsForeachLoop(LgsLoopVar* loopVar, LogosExpr* iterableExpr, LgsStmtBlock* stmtBlock) : loopVar(loopVar), iterableExpr(iterableExpr), stmtBlock(stmtBlock) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsForeachLoop() override;
};


#endif //LOGOSFOREACHLOOP_H
