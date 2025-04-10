#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LgsLoop.h"

#include <exprs/unary/LgsIterable.h>
#include <exprs/unary/LgsUnaryExpr.h>

class LgsArrayType;

class LgsForeachLoop final : public LgsLoop {
public:
    LgsUnaryExpr* iterableExpr = nullptr;

    LgsForeachLoop(const vector<LgsVarDec*>& loopVars, LgsUnaryExpr* iterable, LgsStmtBlock* stmtBlock) : LgsLoop(loopVars, stmtBlock), iterableExpr(iterable) {}
    int loopStart() override;
    int loopEnd() override;
    void setIRLoopVariable(CodeGenMetadata* metadata) override;
    LgsIterable* getExprAsIterable() const;
    ~LgsForeachLoop() override;
};


#endif //LOGOSFOREACHLOOP_H
