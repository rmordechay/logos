#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LgsLoop.h"
#include <exprs/unary/LgsUnaryExpr.h>

class LgsDArrayType;

class LgsForeachLoop final : public LgsLoop {
public:
    LgsUnaryExpr* iterExpr = nullptr;

    explicit LgsForeachLoop(LgsUnaryExpr* iterable) : iterExpr(iterable) {}
    Value* loopStart(CodeGenMetadata* metadata) override;
    Value* loopEnd(CodeGenMetadata* metadata) override;
    void setIRLoopVars(CodeGenMetadata* metadata) override;
    ~LgsForeachLoop() override;
};

#endif //LOGOSFOREACHLOOP_H
