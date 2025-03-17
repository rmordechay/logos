#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LogosLoop.h"

#include <LogosUnaryExpr.h>

class LgsIterable;

class LgsForeachLoop final : public LgsLoop {
public:
    LgsUnaryExpr* iterable = nullptr;

    LgsForeachLoop(const vector<LgsVarDec*>& loopVars, LgsUnaryExpr* iterable, LgsStmtBlock* stmtBlock)
        : LgsLoop(loopVars, stmtBlock), iterable(iterable) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    LgsIterable* getExprAsIterable() const;
    ~LgsForeachLoop() override;
};


#endif //LOGOSFOREACHLOOP_H
