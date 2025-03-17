#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LogosLoop.h"

#include <LgsIterable.h>
#include <LogosUnaryExpr.h>

class LgsArrayType;

class LgsForeachLoop final : public LgsLoop {
public:
    LgsUnaryExpr* iterableExpr = nullptr;

    LgsForeachLoop(const vector<LgsVarDec*>& loopVars, LgsUnaryExpr* iterable, LgsStmtBlock* stmtBlock) : LgsLoop(loopVars, stmtBlock), iterableExpr(iterable) {}
    int loopSize() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    LgsIterable* getExprAsIterable() const;
    ~LgsForeachLoop() override;
};


#endif //LOGOSFOREACHLOOP_H
