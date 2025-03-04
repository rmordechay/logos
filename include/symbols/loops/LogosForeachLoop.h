#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LogosLoop.h"

class LogosForeachLoop final : public LogosLoop {
public:
    LogosVariable* loopVar = nullptr;
    LogosExpr* iterableExpr = nullptr;
    LogosArray* iterable = nullptr;
    LogosStmtBlock* stmtBlock = nullptr;
    LogosArrayIndex* arrayIndex = nullptr;

    LogosForeachLoop(LogosVariable* loopVar, LogosExpr* iterableExpr, LogosStmtBlock* stmtBlock) : loopVar(loopVar), iterableExpr(iterableExpr), stmtBlock(stmtBlock) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosForeachLoop() override;
};


#endif //LOGOSFOREACHLOOP_H
