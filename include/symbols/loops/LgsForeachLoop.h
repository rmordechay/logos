#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LogosLoop.h"

class LgsIterable;

class LgsForeachLoop final : public LgsLoop {
public:
    LgsExpr* iterableExpr = nullptr;
    LgsIterable* iterable = nullptr;

    LgsForeachLoop(LgsVariable* loopVar, LgsExpr* iterableExpr, LgsStmtBlock* stmtBlock) : LgsLoop(loopVar, stmtBlock), iterableExpr(iterableExpr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsForeachLoop() override;
};


#endif //LOGOSFOREACHLOOP_H
