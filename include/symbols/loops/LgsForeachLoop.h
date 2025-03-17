#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LogosLoop.h"

class LgsIterable;

class LgsForeachLoop final : public LgsLoop {
public:
    LgsExpr* iterable = nullptr;

    LgsForeachLoop(LgsVarDec* loopVar, LgsExpr* iterableExpr, LgsStmtBlock* stmtBlock) : LgsLoop(loopVar, stmtBlock), iterable(iterableExpr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    LgsIterable* asIterable() const;
    ~LgsForeachLoop() override;
};


#endif //LOGOSFOREACHLOOP_H
