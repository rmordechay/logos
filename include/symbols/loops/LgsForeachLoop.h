#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LgsLoop.h"
#include <exprs/unary/LgsUnaryExpr.h>

class LgsDArrayType;

class LgsForeachLoop final : public LgsLoop {
public:
    LgsUnaryExpr* iterExpr = nullptr;

    LgsForeachLoop(const vector<LgsVarDec*>& loopVars, LgsUnaryExpr* iterable, LgsStmtBlock* stmtBlock) : LgsLoop(loopVars, stmtBlock), iterExpr(iterable) {}
    int loopStart() override;
    int loopEnd() override;
    void setIRLoopVariable(CodeGenMetadata* metadata) override;
    ~LgsForeachLoop() override;
};


#endif //LOGOSFOREACHLOOP_H
