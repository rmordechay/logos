#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LgsLoop.h"
#include <exprs/unary/LgsUnaryExpr.h>

class LgsDArrayType;

class LgsForeachLoop final : public LgsLoop {
public:
    LgsUnaryExpr* expr = nullptr;

    LgsForeachLoop(const vector<LgsVarDec*>& loopVars, LgsUnaryExpr* iterable, LgsStmtBlock* stmtBlock) : LgsLoop(loopVars, stmtBlock), expr(iterable) {}
    int loopStart() override;
    int loopEnd() override;
    void setIRLoopVariable(CodeGenMetadata* metadata) override;
    ~LgsForeachLoop() override;
};


#endif //LOGOSFOREACHLOOP_H
