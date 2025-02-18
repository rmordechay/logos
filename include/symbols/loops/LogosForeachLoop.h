#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LogosLoop.h"

class LogosForeachLoop final : public LogosLoop {
public:
    LogosVariable* loopVar;
    LogosExpr* iterable;
    LogosStmtBlock* stmtBlock;

    LogosForeachLoop(LogosVariable* loopVar, LogosExpr* iterable, LogosStmtBlock* stmtBlock) : loopVar(loopVar), iterable(iterable), stmtBlock(stmtBlock) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
};


#endif //LOGOSFOREACHLOOP_H
